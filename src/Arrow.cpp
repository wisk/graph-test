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

  bool revLine = (_startItem->y() > _endItem->y()) ? true : false;
  _clr = revLine ? Qt::red : Qt::blue;

  QPen pen(_clr);
  QBrush brs(_clr);

  painter->setPen(pen);
  painter->setBrush(brs);
  painter->setRenderHint(QPainter::Antialiasing);

  auto startRect = _startItem->boundingRect();
  auto endRect   = _endItem->boundingRect();

  if (revLine)
    points.push_back(QPointF(_endItem->x() + endRect.width() / 2, _endItem->y() + endRect.height()));
  else
    points.push_back(QPointF(_endItem->x() + endRect.width() / 2, _endItem->y()));

  for (auto it = _bends.begin(); it.valid(); ++it)
    points.push_back(QPointF(startRect.width() / 2 + (*it).m_x, startRect.height() / 2 + (*it).m_y));

  if (revLine)
    points.push_back(QPointF(_startItem->x() + startRect.width() / 2, _startItem->y()));
  else
    points.push_back(QPointF(_startItem->x() + startRect.width() / 2, _startItem->y() + startRect.height()));

  std::list<QLineF> lines;
  auto iterPt = std::begin(points);
  QPointF startPt, endPt;
  startPt = *iterPt;
  ++iterPt;
  for (; iterPt != std::end(points); ++iterPt)
  {
    endPt = *iterPt;
    setLine(startPt.x(), startPt.y(), endPt.x(), endPt.y());
    painter->drawLine(line());
    lines.push_back(QLineF(startPt, endPt));
    startPt = endPt;
  }

  static const qreal Pi = 3.14;
  static const qreal arrowSize = 10.0;
  double angle = ::acos(line().dx() / line().length());
  if (revLine)
    angle = (Pi * 2) - angle;
  QPointF arrowPt = revLine ? lines.front().p1() : lines.front().p1();
  QPointF arrowP1 = arrowPt + QPointF(::sin(angle + Pi / 3)      * arrowSize, ::cos(angle + Pi / 3)      * arrowSize);
  QPointF arrowP2 = arrowPt + QPointF(::sin(angle + Pi - Pi / 3) * arrowSize, ::cos(angle + Pi - Pi / 3) * arrowSize);

  _head.clear();
  _head << arrowPt << arrowP1 << arrowP2;
  QPainterPath headPath;
  headPath.addPolygon(_head);
  headPath.setFillRule(Qt::WindingFill);
  painter->drawPath(headPath);
}

