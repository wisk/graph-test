#include "Arrow.hpp"

Arrow::Arrow(QGraphicsItem * startItem, QGraphicsItem * endItem)
  : _startItem(startItem), _endItem(endItem), _clr(Qt::blue)
{
  setZValue(1.0);
}

QPainterPath Arrow::shape(void) const
{
  QPainterPath path = QGraphicsLineItem::shape();
  path.addPolygon(_head);
  return path;
}

QRectF Arrow::boundingRect(void) const
{
  qreal extra = (pen().width() + 20) / 2.0;

  return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
    line().p2().y() - line().p1().y()))
    .normalized()
    .adjusted(-extra, -extra, extra, extra);
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
  QPointF startPt, endPt;
  auto startBoundingRect = _startItem->boundingRect();
  auto endBoundingRect = _endItem->boundingRect();
  auto startPos = _startItem->pos();
  auto endPos = _endItem->pos();

  startPt.setX(startPos.x() + startBoundingRect.width() / 2);
  startPt.setY(startPos.y() + startBoundingRect.height());
  endPt.setX(endPos.x() + endBoundingRect.width() / 2);
  endPt.setY(endPos.y());

  setLine(QLineF(startPt, endPt));
  painter->drawLine(line());
}

