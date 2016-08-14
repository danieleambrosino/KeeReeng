//
// Created by daniele on 14/08/16
//

#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include <QTreeWidget>

class Database;
class Entry;

class EntryListItem : public QTreeWidgetItem {
 public:
  EntryListItem(Entry *);
  void update();

  Entry *entryData;
};

class EntryList : public QTreeWidget {
 public:
  EntryList(QWidget *parent = nullptr);

  void create(const QString &password);
  void addEntryItem(Entry *);

  Database *db;

 public slots:
  void updateList();

 private:
  QList<EntryListItem *> m_entries; // FIXME
};

#endif // ENTRYLIST_H