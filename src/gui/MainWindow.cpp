#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "core/Entry.h"
#include "core/Database.h"

#include "EnterPasswordDialog.h"
#include "EntryDialog.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionNewDatabase_triggered()
{
  EnterPasswordDialog dlg;
  dlg.exec();
}

void MainWindow::on_actionNewEntry_triggered()
{
  EntryDialog dlg(this);
  if (dlg.exec() == dlg.Rejected)
    return;

  Entry *entry = new Entry(dlg.title(), dlg.username(), dlg.password());
}
