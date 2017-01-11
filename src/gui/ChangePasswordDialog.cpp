#include "ChangePasswordDialog.h"
#include "ui_ChangePasswordDialog.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog) {
  ui->setupUi(this);
}

ChangePasswordDialog::~ChangePasswordDialog() {
  delete ui;
}

void ChangePasswordDialog::on_buttonBox_accepted() {
  m_currentPassword = ui->currentPassword->text();
  if (ui->newPassword->text() != ui->reinsertNewPassword->text()) {
    m_passwordMismatch = true;
    m_newPassword = QString();
    return;
  }

  m_newPassword = ui->newPassword->text();
  m_passwordMismatch = false;
}
