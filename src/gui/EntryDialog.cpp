#include "EntryDialog.h"
#include "ui_EntryDialog.h"

#include "core/Entry.h"
#include "EntryList.h"

EntryDialog::EntryDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EntryDialog)
{
  ui->setupUi(this);
}

EntryDialog::EntryDialog(EntryListItem *entry, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::EntryDialog)
{
  ui->setupUi(this);
  ui->titleLine->setText(entry->entryData->title);
  ui->usernameLine->setText(entry->entryData->username);
  ui->passwordLine->setText(entry->entryData->password);
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
