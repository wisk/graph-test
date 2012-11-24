#include "Arrow.hpp"

Arrow::Arrow(QGraphicsItem * startItem, QGraphicsItem * endItem, ogdf::DPolyline const& bends)
  : _startItem(startItem), _endItem(endItem), _clr(Qt::blue), _bends(bends)
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
  std::list<QPointF> points;

  auto startRect = _startItem->boundingRect();
  auto endRect = _startItem->boundingRect();

  if (_startItem->y() > _endItem->y())
    points.push_back(QPointF(_endItem->x() + endRect.width() / 2, _endItem->y() + endRect.height()));
  else
    points.push_back(QPointF(_endItem->x() + endRect.width() / 2, _endItem->y()));

  for (auto it = _bends.begin(); it.valid(); ++it)
    points.push_back(QPointF(startRect.width() / 2 + (*it).m_x, startRect.height() / 2 + (*it).m_y));

  if (_startItem->y() > _endItem->y())
    points.push_back(QPointF(_startItem->x() + startRect.width() / 2, _startItem->y()));
  else
    points.push_back(QPointF(_startItem->x() + startRect.width() / 2, _startItem->y() + startRect.height()));

  auto iterPt = std::begin(points);
  QPointF startPt, endPt;
  startPt = *iterPt;
  ++iterPt;
  for (; iterPt != std::end(points); ++iterPt)
  {
    endPt = *iterPt;
    painter->setRenderHint(QPainter::Antialiasing);
    setLine(startPt.x(), startPt.y(), endPt.x(), endPt.y());
    if (_startItem->y() > _endItem->y())
    {
      QPen pen(Qt::red);
      painter->setPen(pen);
    }
    painter->drawLine(line());
    startPt = endPt;
  }
}

