#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "core/Database.h"
#include "core/Entry.h"

#include "EnterPasswordDialog.h"
#include "EntryDialog.h"
#include "ExitWithoutSavingDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    neverSaved(false),
    saved(true) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionNewDatabase_triggered() {
  if (not saved)
    on_actionCloseDatabase_triggered();

  EnterPasswordDialog dlg;
  if (dlg.exec() == dlg.Rejected)
    return;

  ui->entryList->create(dlg.password());
  enableInterface(true);
  neverSaved = true;
}

void MainWindow::on_actionOpenDatabase_triggered() {
  if (not saved)
    on_actionCloseDatabase_triggered();

  QFileDialog openDlg(this, "Open database", "/home", "KeeReeng database (*.krdb)");
  openDlg.setAcceptMode(openDlg.AcceptOpen);
  if (openDlg.exec() == openDlg.Rejected)
    return;

  QString filename = openDlg.selectedFiles().first();

  EnterPasswordDialog pwdDlg(this);
  if (pwdDlg.exec() == pwdDlg.Rejected)
    return;

  QString password = pwdDlg.password();
  ui->entryList->db->create(password, filename);
  if (not ui->entryList->db->open()) {
    handleError(ui->entryList->db->error());
    return;
  }

  neverSaved = false;
  ui->entryList->updateList();
  enableInterface(true);
}

void MainWindow::on_actionCloseDatabase_triggered() {
  if (not saved)
    on_actionSave_triggered();

  ui->entryList->clear();
  enableInterface(false);
}

void MainWindow::on_actionSave_triggered() {
  if (neverSaved)
    on_actionSaveAs_triggered();
  else if (not saved)
    ui->entryList->db->save();

  saved = true;
}

void MainWindow::on_actionSaveAs_triggered() {
  QFileDialog saveDlg(this, "Save as...", "/home", "KeeReeng database (*.krdb)");
  saveDlg.setAcceptMode(saveDlg.AcceptSave);
  if (saveDlg.exec() == saveDlg.Rejected)
    return;

  QString filename = saveDlg.selectedFiles().first();
  if (not ui->entryList->db->saveAs(filename)) {
    handleError(ui->entryList->db->error());
    return;
  }

  neverSaved = false;
  return;
}

void MainWindow::on_actionQuit_triggered() {
  if (not saved) {
    ExitWithoutSavingDialog dlg(this);
    int result = dlg.exec();
    if (result == dlg.Rejected)
      return;
    else if (result == dlg.Accepted)
      on_actionSave_triggered();
    else if (result == dlg.CloseNoSave)
      close();
  }
  close();
}

void MainWindow::on_actionNewEntry_triggered() {
  EntryDialog dlg(this);
  if (dlg.exec() == dlg.Rejected)
    return;

  Entry *entry = new Entry(dlg.title(), dlg.username(), dlg.password());
  ui->entryList->addEntryItem(entry);

  saved = false;
}

void MainWindow::on_entryList_itemDoubleClicked(QTreeWidgetItem *item,
                                                int column) {
  EntryListItem *entryItem = static_cast<EntryListItem *>(item);
  EntryDialog dlg(entryItem, this);
  if (dlg.exec() == dlg.Rejected)
    return;

  entryItem->entryData->title = dlg.title();
  entryItem->entryData->username = dlg.username();
  entryItem->entryData->password = dlg.password();

  ui->entryList->updateList();
  saved = false;
}

void MainWindow::enableInterface(bool value) {
  ui->actionCloseDatabase->setEnabled(value);
  ui->actionChangeMasterPassword->setEnabled(value);
  ui->actionSave->setEnabled(value);
  ui->actionSaveAs->setEnabled(value);
  ui->menuEntries->setEnabled(value);
  ui->entryList->setEnabled(value);
}

void MainWindow::handleError(int error) {
  switch (error) {
    case Database::NoError:
      break;
    case Database::CorruptedDatabase:
      QMessageBox::critical(this, "Corrupted error", "Database is corrupted!");
      break;
    case Database::WrongPassword:
      QMessageBox::warning(this, "Wrong password", "Wrong password!");
      break;
    case Database::FileNotWritable:
      QMessageBox::critical(this, "File not writable", "Unable to write file!");
      break;
    case Database::FileNotReadable:
      QMessageBox::critical(this, "File not readable", "Unable to read file!");
      break;
    default:break;
  }
}
