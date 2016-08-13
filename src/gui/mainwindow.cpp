#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "enterpassworddialog.h"

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
