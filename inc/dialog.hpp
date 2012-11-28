#ifndef dialog_h__
#define dialog_h__

#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include "ControlFlowGraphScene.hpp"

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget * parent = 0);
  ~MainWindow(void);


private:
  Ui::MainWindow *ui;
  ControlFlowGraphScene *scene;
  typedef std::vector<QGraphicsItem *> VectorItem;
  VectorItem items;
};

#endif // dialog_h__
