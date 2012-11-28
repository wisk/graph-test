#ifndef ControlFlowGraphView_h__
#define ControlFlowGraphView_h__

#include <QtCore>
#include <QtGui>
#include <QGraphicsView>

// src: http://www.qtcentre.org/threads/35738-How-to-zooming-like-in-AutoCAD-with-QGraphicsView
class ControlFlowGraphView : public QGraphicsView
{
  Q_OBJECT
public:
  ControlFlowGraphView(QWidget * parent = 0) : QGraphicsView(parent) {}
  void zoom(qreal factor, QPointF centerPt);

protected:
  virtual void wheelEvent(QWheelEvent *event);
private:
};

#endif // ControlFlowGraphView_h__
