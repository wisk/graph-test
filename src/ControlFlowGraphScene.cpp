#include "ControlFlowGraphScene.hpp"
#include "Arrow.hpp"

void ControlFlowGraphScene::drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget /*= 0*/)
{
  for (int i = 0; i < numItems; ++i)
  {
    // Draw the item
    painter->save();
    painter->setMatrix(items[i]->sceneMatrix(), true);
    items[i]->paint(painter, &options[i], widget);
    painter->restore();
  }
}

void ControlFlowGraphScene::refreshArrows(void)
{
  auto allItems = items();
  for (int i = 0; i < allItems.size(); ++i)
  {
    auto arrow = dynamic_cast<Arrow *>(allItems.at(i));
    if (arrow == nullptr) continue;
    arrow->computeCoordinates();
    update(arrow->boundingRect());
    arrow->update();
  }
}