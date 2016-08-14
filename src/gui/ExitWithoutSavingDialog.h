#ifndef EXITWITHOUTSAVINGDIALOG_H
#define EXITWITHOUTSAVINGDIALOG_H

#include <QDialog>

namespace Ui {
class ExitWithoutSavingDialog;
}

class ExitWithoutSavingDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit ExitWithoutSavingDialog(QWidget *parent = 0);
    ~ExitWithoutSavingDialog();

  private:
    Ui::ExitWithoutSavingDialog *ui;
};

#endif // EXITWITHOUTSAVINGDIALOG_H
