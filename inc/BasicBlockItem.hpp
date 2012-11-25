#ifndef BasicBlockItem_h__
#define BasicBlockItem_h__

#include <QPainter>
#include <QGraphicsItem>

class BasicBlockItem : public QGraphicsItem
{
public:
  BasicBlockItem(qreal width, qreal height, int id);

  QRectF boundingRect(void) const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
  qreal _width, _height;
  bool _isPress;
  int _id;
  qreal _z;
};

#endif // BasicBlockItem_h__
