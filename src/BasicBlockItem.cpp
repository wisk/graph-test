#include "BasicBlockItem.hpp"
#include <QObject>
#include <sstream>

BasicBlockItem::BasicBlockItem(QObject * parent, qreal width, qreal height, int id)
  : _parent(parent), _width(width), _height(height), _isPress(false), _id(id), _z(zValue())
{
  setFlag(ItemIsMovable);
  connect(this, SIGNAL(moved()), _parent, SLOT(refreshArrows()));
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
  std::ostringstream oss;
  oss << "bb_" << _id;
  painter->drawText(10, 10, QString::fromStdString(oss.str()));
  painter->drawRect(rect);
}

void BasicBlockItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  _isPress = true;
  setZValue(1.0);
  update();
  QGraphicsItem::mousePressEvent(event);
  emit moved();
}

void BasicBlockItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  _isPress = false;
  setZValue(_z);
  QGraphicsItem::mouseReleaseEvent(event);
  emit moved();
}
