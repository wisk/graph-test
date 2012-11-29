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

  const int Len = 40;
  node lastNode = nullptr;
  std::vector<node> nodes;
  nodes.reserve(Len);
  for (int i = 0; i < Len; ++i)
  {
    auto newNode = G.newNode();
    GA.width()[newNode] = static_cast<double>(100 + rand() % 50);
    GA.height()[newNode] = static_cast<double>(100 + rand() % 50);
    nodes.push_back(newNode);
  }

  std::vector<edge> edges;
  for (int i = 0; i < Len * 2; ++i)
    edges.push_back(G.newEdge(nodes[rand() % Len], nodes[rand() % Len]));
  //edges.push_back(G.newEdge(nodes[0], nodes[1]));
  //edges.push_back(G.newEdge(nodes[0], nodes[2]));
  //edges.push_back(G.newEdge(nodes[1], nodes[3]));
  //edges.push_back(G.newEdge(nodes[2], nodes[3]));
  //edges.push_back(G.newEdge(nodes[3], nodes[4]));
  //edges.push_back(G.newEdge(nodes[4], nodes[5]));
  //edges.push_back(G.newEdge(nodes[5], nodes[4]));
  //edges.push_back(G.newEdge(nodes[5], nodes[6]));
  //edges.push_back(G.newEdge(nodes[6], nodes[7]));
  //edges.push_back(G.newEdge(nodes[6], nodes[8]));
  //edges.push_back(G.newEdge(nodes[6], nodes[9]));
  //edges.push_back(G.newEdge(nodes[7], nodes[10]));
  //edges.push_back(G.newEdge(nodes[8], nodes[10]));
  //edges.push_back(G.newEdge(nodes[9], nodes[10]));

  SugiyamaLayout SL;
  auto FHL = new FastHierarchyLayout;
  FHL->nodeDistance(25.0);
  FHL->layerDistance(25.0);
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

