#ifndef ENTERPASSWORDDIALOG_H
#define ENTERPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class EnterPasswordDialog;
}

class EnterPasswordDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit EnterPasswordDialog(QWidget *parent = nullptr);
    ~EnterPasswordDialog();

  private:
    Ui::EnterPasswordDialog *ui;
};

#endif // ENTERPASSWORDDIALOG_H
