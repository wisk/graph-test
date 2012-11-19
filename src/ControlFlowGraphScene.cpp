#include "ControlFlowGraphScene.hpp"

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

