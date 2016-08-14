#include "EntryDialog.h"
#include "ui_EntryDialog.h"

EntryDialog::EntryDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EntryDialog)
{
  ui->setupUi(this);
}

EntryDialog::~EntryDialog()
{
  delete ui;
}

QString EntryDialog::title() {
  return ui->titleLine->text();
}

QString EntryDialog::username() {
  return ui->usernameLine->text();
}

QString EntryDialog::password() {
  return ui->passwordLine->text();
}
