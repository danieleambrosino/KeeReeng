#include "enterpassworddialog.h"
#include "ui_enterpassworddialog.h"

EnterPasswordDialog::EnterPasswordDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EnterPasswordDialog)
{
  ui->setupUi(this);
}

EnterPasswordDialog::~EnterPasswordDialog()
{
  delete ui;
}
