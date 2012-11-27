#ifndef Arrow_h__
#define Arrow_h__

#include <QAbstractGraphicsShapeItem>
#include <QPen>
#include <QPainter>
#include <ogdf/basic/geometry.h>

class Edge : public QAbstractGraphicsShapeItem
{
public:
  enum { Type = UserType + 1 };

  Edge(QGraphicsItem * startItem, QGraphicsItem * endItem, ogdf::DPolyline const& bends);

  int type(void) const { return Type; }
  virtual QRectF boundingRect(void) const;
  virtual QPainterPath shape() const;
  void computeCoordinates(void);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
  QGraphicsItem *_startItem, *_endItem;
  ogdf::DPolyline _bends;
  QColor _clr;
  QPainterPath _line;
  QPainterPath _head;
};

#endif // Arrow_h__
