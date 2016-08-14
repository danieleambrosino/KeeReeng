#include "ExitWithoutSavingDialog.h"
#include "ui_ExitWithoutSavingDialog.h"

ExitWithoutSavingDialog::ExitWithoutSavingDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ExitWithoutSavingDialog)
{
  ui->setupUi(this);
}

ExitWithoutSavingDialog::~ExitWithoutSavingDialog()
{
  delete ui;
}
