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
  /**
   * "File" menu
   */
  void on_actionNewDatabase_triggered();
  void on_actionOpenDatabase_triggered();
  void on_actionSave_triggered();
  void on_actionSaveAs_triggered();
  void on_actionCloseDatabase_triggered();
  void on_actionChangeMasterPassword_triggered();
  void on_actionQuit_triggered();

  /**
   * "Entry" menu
   */
  void on_actionNewEntry_triggered();

  void on_entryList_itemDoubleClicked(QTreeWidgetItem *item, int column);
  void showEntryContextMenu(const QPoint &pos);

  private:
  void enableInterface(bool);
  int handleError(int);

  Ui::MainWindow *ui;
  bool saved;
  bool neverSaved;
};

#endif // MAINWINDOW_H
