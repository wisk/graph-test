#ifndef Arrow_h__
#define Arrow_h__

#include <QGraphicsLineItem>
#include <QPen>
#include <QPainter>
#include <ogdf/basic/geometry.h>

class Arrow : public QGraphicsLineItem
{
public:
  enum { Type = UserType + 1 };

  Arrow(QGraphicsItem * startItem, QGraphicsItem * endItem, ogdf::DPolyline const& bends);

  int type(void) const { return Type; }
  virtual QRectF boundingRect(void) const;
  virtual QPainterPath shape() const;

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
  QGraphicsItem *_startItem, *_endItem;
  ogdf::DPolyline _bends;
  QColor _clr;
  QPolygonF _head;
};

#endif // Arrow_h__
