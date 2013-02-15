#include "dialog.hpp"
#include "ui_graph.h"

#include "Arrow.hpp"
#include "BasicBlockItem.hpp"

#include <QMessageBox>

#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/FastHierarchyLayout.h>

MainWindow::MainWindow(QWidget * parent /*= 0*/) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  scene = new ControlFlowGraphScene(this);
  ui->graphicsView->setScene(scene);

  using namespace ogdf;

  Graph G;
  GraphAttributes GA(G, GraphAttributes::nodeGraphics | GraphAttributes::edgeGraphics);

  const int Len = 5;
  node lastNode = nullptr;
  std::vector<node> nodes;
  nodes.reserve(Len);
  for (int i = 0; i < Len; ++i)
  {
    auto newNode = G.newNode();
    GA.width()[newNode] = static_cast<double>(100 + rand() % 500);
    GA.height()[newNode] = static_cast<double>(100 + rand() % 200);
    nodes.push_back(newNode);
  }

  std::vector<edge> edges;
  for (int i = 0; i < Len * 2; ++i)
    edges.push_back(G.newEdge(nodes[rand() % Len], nodes[rand() % Len]));

  SugiyamaLayout SL;
  auto FHL = new FastHierarchyLayout;
  FHL->nodeDistance(25.0);
  FHL->layerDistance(100.0);
  SL.setLayout(FHL);
  SL.call(GA);

  GA.writeGML("test.gml");

  int i = 0;
  node v;
  std::vector<QGraphicsItem*> items;
  forall_nodes(v, G)
  {
    auto curNode = nodes[i];
    auto bbItem = new BasicBlockItem(scene, GA.width()[curNode], GA.height()[curNode], i++);
    items.push_back(bbItem);
    bbItem->moveBy(GA.x(v), GA.y(v));
    scene->addItem(bbItem);
  }

  forall_nodes(v, G)
  {
    edge e;
    forall_adj_edges(e, v)
    {
      auto bends = GA.bends(e);
      auto bbEdge = new Edge(items[e->source()->index()], items[e->target()->index()], bends);
      scene->addItem(bbEdge);
    }
  }
}

MainWindow::~MainWindow(void)
{
  delete ui;

  std::for_each(std::begin(items), std::end(items), [](QGraphicsItem *gfxItem) { delete gfxItem; });
}

