//
// Created by daniele on 14/08/16
//

#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include <QTreeWidget>

#include "core/Database.h"

class Entry;

class EntryListItem : public QTreeWidgetItem {
 public:
  EntryListItem(Entry *);
  void update();

  Entry *entryData;
};

class EntryList : public QTreeWidget, public Database {
  Q_OBJECT

 public:
  EntryList(QWidget *parent = nullptr);
  void addItem(Entry *);
  void updateView();
  void clear();
  using Database::create;

 private:
  QList<EntryListItem *> items;
};

#endif // ENTRYLIST_H