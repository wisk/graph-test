#ifndef ControlFlowGraphScene_h__
#define ControlFlowGraphScene_h__

#include <QtCore>
#include <QtGui>

class ControlFlowGraphScene : public QGraphicsScene
{
  Q_OBJECT
public:
  explicit ControlFlowGraphScene(QObject * parent = 0) : QGraphicsScene(parent) {}

  virtual void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget = 0);

public slots:
  void refreshArrows(void);

private:
};

#endif // ControlFlowGraphScene_h__
