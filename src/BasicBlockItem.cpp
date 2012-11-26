#include "BasicBlockItem.hpp"

BasicBlockItem::BasicBlockItem(qreal width, qreal height, int id) : _width(width), _height(height), _isPress(false), _id(id), _z(zValue())
{
  setFlag(ItemIsMovable);
}

QRectF BasicBlockItem::boundingRect(void) const
{
  return QRectF(0, 0, _width, _height);
}

void BasicBlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= 0*/)
{
  QRectF rect = boundingRect();
  QBrush brush(Qt::lightGray);
  qreal opacity = 1.0;

  if (_isPress)
  {
    brush.setColor(Qt::blue);
    opacity = 0.5;
  }

  setOpacity(opacity);
  painter->fillRect(rect, brush);
  char buf[20];
  itoa(_id, buf, 10);
  painter->drawText(rect, buf);
  painter->drawRect(rect);
}

void BasicBlockItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  _isPress = true;
  setZValue(1.0);
  update();
  QGraphicsItem::mousePressEvent(event);
}

void BasicBlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  _isPress = false;
  setZValue(_z);
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}

