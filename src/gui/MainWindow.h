#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTreeWidgetItem;

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void on_actionNewDatabase_triggered();
  void on_actionNewEntry_triggered();
  void on_entryList_itemDoubleClicked(QTreeWidgetItem *item, int column);
  void on_actionSave_triggered();
  void on_actionOpenDatabase_triggered();
  void on_actionQuit_triggered();
  void on_actionCloseDatabase_triggered();

  void on_actionSaveAs_triggered();

  private:
  void enableInterface(bool);
  void handleError(int);

  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
