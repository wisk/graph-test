#ifndef dialog_h__
#define dialog_h__

#include <QtCore>
#include <QtGui>
#include <QDialog>
#include "ControlFlowGraphScene.hpp"

namespace Ui
{
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget * parent = 0);
  ~Dialog(void);


private:
  Ui::Dialog *ui;
  ControlFlowGraphScene *scene;
  typedef std::vector<QGraphicsItem *> VectorItem;
  VectorItem items;
};

#endif // dialog_h__