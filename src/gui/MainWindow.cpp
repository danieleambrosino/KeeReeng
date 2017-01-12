#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QClipboard>

#include "core/Entry.h"

#include "EnterPasswordDialog.h"
#include "EntryDialog.h"
#include "ExitWithoutSavingDialog.h"
#include "ChangePasswordDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    neverSaved(false),
    saved(true) {
  ui->setupUi(this);
  connect(ui->entryList, &EntryList::customContextMenuRequested, this, &MainWindow::showEntryContextMenu);
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
  ui->entryList->create(password, filename);
  if (not ui->entryList->open()) {
    handleError(ui->entryList->error());
    return;
  }

  neverSaved = false;
  ui->entryList->updateView();
  enableInterface(true);
}

void MainWindow::on_actionCloseDatabase_triggered() {
  if (not saved)
    on_actionSave_triggered();

  ui->entryList->clear();
  enableInterface(false);
}

void MainWindow::on_actionChangeMasterPassword_triggered() {
  ChangePasswordDialog dlg;

  while (dlg.exec() != dlg.Rejected) {
    if (dlg.passwordMismatch()) {
      QMessageBox::warning(this,
                           "Error",
                           "Password mismatch!");
      continue;
    }

    if (not ui->entryList->changePassword(dlg.currentPassword(),
                                          dlg.newPassword())) {
      QMessageBox::warning(this,
                           "Incorrect password",
                           "Current password is wrong!");
      continue;
    }

    else {
      saved = false;
      on_actionSave_triggered();
      return;
    }
  }
}

void MainWindow::on_actionSave_triggered() {
  if (neverSaved)
    on_actionSaveAs_triggered();
  else if (not saved)
    ui->entryList->save();

  saved = not neverSaved;
  if (not saved)
    QMessageBox::warning(this, "Database not saved", "Warning: database not saved!");
}

void MainWindow::on_actionSaveAs_triggered() {
  QFileDialog saveDlg(this, "Save as...", "/home", "KeeReeng database (*.krdb)");
  saveDlg.setAcceptMode(saveDlg.AcceptSave);

  int errorCode = Database::NoError;
  QString filename;

  do {
    if (saveDlg.exec() == 0)
      return;

    filename = saveDlg.selectedFiles().first();
    if (not ui->entryList->saveAs(filename))
      errorCode = handleError(ui->entryList->error());
  } while (errorCode == Database::FileNotWriteable);

  neverSaved = not (errorCode == Database::NoError);

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
  ui->entryList->addItem(entry);

  /*
   * Using Observer design pattern:
   * everytime an entry (the subject) is created/modified,
   * it notifies the database (the observer)
   * through the "Save_triggered" method,
   * which eventually provides a GUI for the user
   * if he never saved before the DB.
   * The database is updated automatically
   * and the db file is serialized and encrypted constantly.
   */

  saved = false;

  on_actionSave_triggered();
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

  ui->entryList->updateView();
  saved = false;

  on_actionSave_triggered();
}

void MainWindow::showEntryContextMenu(const QPoint &pos) {
  EntryList *list = ui->entryList;
  EntryListItem *item = static_cast<EntryListItem *>(list->itemAt(pos));

  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(item->entryData->password);

  QMessageBox::information(this, "Copied!", "Password copied to clipboard!");
}

void MainWindow::enableInterface(bool value) {
  ui->actionCloseDatabase->setEnabled(value);
  ui->actionChangeMasterPassword->setEnabled(value);
  ui->actionSave->setEnabled(value);
  ui->actionSaveAs->setEnabled(value);
  ui->menuEntries->setEnabled(value);
  ui->entryList->setEnabled(value);
}

int MainWindow::handleError(int error) {
  switch (error) {
    case Database::NoError:
      return Database::NoError;
    case Database::CorruptedDatabase:
      QMessageBox::critical(this, "Corrupted error", "Database is corrupted!");
      return Database::CorruptedDatabase;
    case Database::WrongPassword:
      QMessageBox::warning(this, "Wrong password", "Wrong password!");
      return Database::WrongPassword;
    case Database::FileNotWriteable:
      QMessageBox::critical(this, "File not writable", "Unable to write file!");
      return Database::FileNotWriteable;
    case Database::FileNotReadable:
      QMessageBox::critical(this, "File not readable", "Unable to read file!");
      return Database::FileNotReadable;
    default:return -1;
  }
}
