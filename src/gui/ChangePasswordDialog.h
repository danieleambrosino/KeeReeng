#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog {
 Q_OBJECT

 public:
  explicit ChangePasswordDialog(QWidget *parent = 0);
  ~ChangePasswordDialog();

  const QString &currentPassword() const { return m_currentPassword; }
  const QString &newPassword() const { return m_newPassword; }

  bool passwordMismatch() const { return m_passwordMismatch; }

 private slots:
  void on_buttonBox_accepted();

 private:
  Ui::ChangePasswordDialog *ui;
  QString m_currentPassword;
  QString m_newPassword;
  bool m_passwordMismatch;
};

#endif // CHANGEPASSWORDDIALOG_H
