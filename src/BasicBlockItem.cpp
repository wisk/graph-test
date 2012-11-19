#include "BasicBlockItem.hpp"
#include <boost/lexical_cast.hpp>

BasicBlockItem::BasicBlockItem(int id) : _isPress(false), _id(id), _z(zValue())
{
  setFlag(ItemIsMovable);
}

QRectF BasicBlockItem::boundingRect(void) const
{
  return QRectF(0, 0, 100, 100);
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
  painter->drawText(rect, boost::lexical_cast<std::string>(_id).c_str());
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

