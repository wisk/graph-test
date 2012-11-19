#include "dialog.hpp"
#include "ui_graph.h"

#include "Arrow.hpp"
#include "BasicBlockItem.hpp"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>
#include <boost/graph/fruchterman_reingold.hpp>


Dialog::Dialog(QWidget * parent /*= 0*/) : QDialog(parent), ui(new Ui::Dialog)
{
  ui->setupUi(this);

  scene = new ControlFlowGraphScene(this);
  ui->graphicsView->setScene(scene);

  using namespace boost;
  typedef adjacency_list<> GraphType;
  GraphType graph;
  add_edge(1, 2, graph);
  add_edge(1, 3, graph);
  add_edge(1, 4, graph);
  add_edge(2, 4, graph);
  add_edge(2, 2, graph);
  add_edge(2, 5, graph);
  add_edge(6, 4, graph);
  add_edge(6, 4, graph);
  add_edge(6, 9, graph);
  add_edge(9, 7, graph);
  add_edge(0, 3, graph);
  add_edge(8, 9, graph);

  typedef rectangle_topology<> TopologyType;
  typedef TopologyType::point_type PointType;
  typedef std::vector<PointType> PointVectorType;
  typedef iterator_property_map<
    PointVectorType::iterator, property_map<GraphType, vertex_index_t>::type> PositionMapType;
  typedef graph_traits<GraphType>::vertex_iterator VerterIteratorType;

  PointVectorType points;
  points.resize(num_vertices(graph));
  PositionMapType pos = PositionMapType(points.begin(), get(vertex_index, graph));
  auto rectScene = scene->sceneRect();
  rectangle_topology<> topo(-1000.0, -1000.0, 1000.0, 1000.0);
  fruchterman_reingold_force_directed_layout(graph, pos, topo);

  VerterIteratorType vtx_iter, vtx_end;
  int id = 0;
  BasicBlockItem * lastItem = nullptr;
  for (tie(vtx_iter, vtx_end) = vertices(graph); vtx_iter != vtx_end; ++vtx_iter)
  {
    auto curItem = new BasicBlockItem(id++);
    curItem->moveBy(pos[*vtx_iter][0], pos[*vtx_iter][1]);
    items.push_back(curItem);
    scene->addItem(curItem);

    if (lastItem == nullptr)
      lastItem = curItem;
    else if (rand() & 1)
      lastItem = curItem;
    else
      scene->addItem(new Arrow(lastItem, curItem));
  }

}

Dialog::~Dialog(void)
{
  delete ui;

  std::for_each(std::begin(items), std::end(items), [](QGraphicsItem *gfxItem) { delete gfxItem; });
}

