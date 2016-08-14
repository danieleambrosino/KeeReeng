#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class EntryDialog;
}

class EntryListItem;

class EntryDialog : public QDialog {
 Q_OBJECT

 public:
  explicit EntryDialog(QWidget *parent = nullptr);
  EntryDialog(EntryListItem *entry, QWidget *parent = nullptr);
  ~EntryDialog();

  QString title();
  QString username();
  QString password();

 private:
  Ui::EntryDialog *ui;
};

#endif // ENTRYDIALOG_H
