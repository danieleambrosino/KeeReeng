#include "EnterPasswordDialog.h"
#include "ui_EnterPasswordDialog.h"

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

QString EnterPasswordDialog::password() {
  return ui->passwordLine->text();
}
