#ifndef EXITWITHOUTSAVINGDIALOG_H
#define EXITWITHOUTSAVINGDIALOG_H

#include <QDialog>

namespace Ui {
class ExitWithoutSavingDialog;
}

class ExitWithoutSavingDialog : public QDialog {
 Q_OBJECT

 public:
  explicit ExitWithoutSavingDialog(QWidget *parent = 0);
  ~ExitWithoutSavingDialog();

  const int CloseNoSave = 3;

 private slots:
  void on_yesButton_clicked();
  void on_noButton_clicked();
  void on_cancelButton_clicked();

  private:
  Ui::ExitWithoutSavingDialog *ui;
};

#endif // EXITWITHOUTSAVINGDIALOG_H
