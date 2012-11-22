#include "dialog.hpp"
#include "ui_graph.h"

#include "Arrow.hpp"
#include "BasicBlockItem.hpp"

#include <QMessageBox>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/layered/SugiyamaLayout.h>

Dialog::Dialog(QWidget * parent /*= 0*/) : QDialog(parent), ui(new Ui::Dialog)
{
  //try
  {
    ui->setupUi(this);

    scene = new ControlFlowGraphScene(this);
    ui->graphicsView->setScene(scene);

    using namespace ogdf;

    Graph G;
    GraphAttributes GA(G, GraphAttributes::nodeGraphics | GraphAttributes::edgeGraphics);

    const int Len = 11;
    node lastNode = nullptr;
    std::vector<node> nodes;
    nodes.reserve(Len);
    for (int i = 0; i < Len; ++i)
      nodes.push_back(G.newNode());

    std::vector<edge> edges;
    edges.push_back(G.newEdge(nodes[0], nodes[1]));
    edges.push_back(G.newEdge(nodes[0], nodes[2]));
    edges.push_back(G.newEdge(nodes[1], nodes[3]));
    edges.push_back(G.newEdge(nodes[2], nodes[3]));
    edges.push_back(G.newEdge(nodes[3], nodes[4]));
    edges.push_back(G.newEdge(nodes[4], nodes[5]));
    edges.push_back(G.newEdge(nodes[5], nodes[4]));
    edges.push_back(G.newEdge(nodes[5], nodes[6]));
    edges.push_back(G.newEdge(nodes[6], nodes[7]));
    edges.push_back(G.newEdge(nodes[6], nodes[8]));
    edges.push_back(G.newEdge(nodes[6], nodes[9]));
    edges.push_back(G.newEdge(nodes[7], nodes[10]));
    edges.push_back(G.newEdge(nodes[8], nodes[10]));
    edges.push_back(G.newEdge(nodes[9], nodes[10]));

    GA.setAllHeight(110);
    GA.setAllWidth(110);

    SugiyamaLayout SL;
    SL.call(GA);

    int i = 0;
    node v;
    std::vector<QGraphicsItem*> items;
    forall_nodes(v, G)
    {
      auto bbItem = new BasicBlockItem(i++);
      items.push_back(bbItem);
      bbItem->moveBy(GA.x(v), GA.y(v));
      scene->addItem(bbItem);
    }

    edge e;
    forall_edges(e, G)
    {
      auto bbEdge = new Arrow(items[e->source()->index()], items[e->target()->index()]);
      scene->addItem(bbEdge);
    }
  }
  //catch (ogdf::Exception const& e)
  //{
  //  QMessageBox::warning(this, "OGDF exception", typeid(e).name());
  //}
}

Dialog::~Dialog(void)
{
  delete ui;

  std::for_each(std::begin(items), std::end(items), [](QGraphicsItem *gfxItem) { delete gfxItem; });
}

