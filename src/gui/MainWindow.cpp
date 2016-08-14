#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "core/Database.h"
#include "core/Entry.h"

#include "EnterPasswordDialog.h"
#include "EntryDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionNewDatabase_triggered() {
  EnterPasswordDialog dlg;
  dlg.exec();

  ui->entryList->create(dlg.password());
  enableInterface(true);
}

void MainWindow::on_actionNewEntry_triggered() {
  EntryDialog dlg(this);
  if (dlg.exec() == dlg.Rejected)
    return;

  Entry *entry = new Entry(dlg.title(), dlg.username(), dlg.password());
  ui->entryList->addEntryItem(entry);
}

void MainWindow::enableInterface(bool value) {
  ui->actionCloseDatabase->setEnabled(value);
  ui->actionChangeMasterPassword->setEnabled(value);
  ui->actionSave->setEnabled(value);
  ui->actionSaveAs->setEnabled(value);
  ui->menuEntries->setEnabled(value);
  ui->entryList->setEnabled(value);
}

void MainWindow::on_entryList_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
  EntryListItem *entryItem = static_cast<EntryListItem *>(item);
  EntryDialog dlg(entryItem, this);
  if (dlg.exec() == dlg.Rejected)
    return;

  entryItem->entryData->title = dlg.title();
  entryItem->entryData->username = dlg.username();
  entryItem->entryData->password = dlg.password();

  ui->entryList->updateList();
}
