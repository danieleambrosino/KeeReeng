#include "ExitWithoutSavingDialog.h"
#include "ui_ExitWithoutSavingDialog.h"

ExitWithoutSavingDialog::ExitWithoutSavingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitWithoutSavingDialog) {
  ui->setupUi(this);
}

ExitWithoutSavingDialog::~ExitWithoutSavingDialog() {
  delete ui;
}

void ExitWithoutSavingDialog::on_yesButton_clicked() {
  emit accept();
}

void ExitWithoutSavingDialog::on_noButton_clicked() {
  emit done(CloseNoSave);
}

void ExitWithoutSavingDialog::on_cancelButton_clicked() {
  emit reject();
}
