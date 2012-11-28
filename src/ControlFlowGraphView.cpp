#include "ControlFlowGraphView.hpp"

void ControlFlowGraphView::zoom(qreal factor, QPointF centerPt)
{
  scale(factor, factor);
  centerOn(centerPt);
}

void ControlFlowGraphView::wheelEvent(QWheelEvent *event)
{
  if (event->modifiers().testFlag(Qt::ControlModifier))
  {
    int numSteps = event->delta() / 15 / 8;

    if (numSteps != 0)
    {
      qreal sc = pow(1.25, numSteps);
      zoom(sc, mapToScene(event->pos()));
      event->accept();
    }
  }
  QGraphicsView::wheelEvent(event);
}

