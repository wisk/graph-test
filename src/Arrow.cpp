#include "Arrow.hpp"

Arrow::Arrow(QGraphicsItem * startItem, QGraphicsItem * endItem, ogdf::DPolyline const& bends)
  : _startItem(startItem), _endItem(endItem), _clr(Qt::blue), _bends(bends)
{
  setZValue(1.0);
}

QPainterPath Arrow::shape(void) const
{
  std::vector<QPointF> points;
  points.reserve(2 + _bends.size());
  auto startRect = _startItem->boundingRect();
  auto endRect   = _endItem->boundingRect();
  bool revLine = (_startItem->y() > _endItem->y()) ? true : false;

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

  QPainterPath path;

  path.moveTo(points.front());
  for (size_t i = points.size(); i + 2 < points.size(); ++i)
    path.cubicTo(points[i], points[i + 1], points[i + 2]);

  //QPolygonF poly;
  //for (auto it = std::begin(points); it != std::end(points); ++it)
  //  poly << *it;

  //path.addPolygon(poly);
  path.addPolygon(_head);
  return path;
}

QRectF Arrow::boundingRect(void) const
{
  return shape().boundingRect();
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
    lines.push_back(QLineF(startPt, endPt));
    startPt = endPt;
  }

  static const qreal Pi = 3.14;
  static const qreal arrowSize = 10.0;
  auto refLine = revLine ? lines.front() : lines.back();
  double angle = ::acos(refLine.dx() / refLine.length());
  if (revLine)
    angle = (Pi * 2) - angle;
  QPointF arrowPt = revLine ? lines.front().p1() : lines.front().p1();
  QPointF arrowP1 = arrowPt + QPointF(::sin(angle + Pi / 3)      * arrowSize, ::cos(angle + Pi / 3)      * arrowSize);
  QPointF arrowP2 = arrowPt + QPointF(::sin(angle + Pi - Pi / 3) * arrowSize, ::cos(angle + Pi - Pi / 3) * arrowSize);

  _head.clear();
  _head << arrowPt << arrowP1 << arrowP2;
  QPainterPath headPath;
  headPath.addPath(this->shape());
  headPath.addPolygon(_head);
  headPath.setFillRule(Qt::WindingFill);
  painter->drawPath(headPath);
}

