//
// Created by daniele on 14/08/16
//

#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include <QTreeWidget>

class Entry;

class EntryListItem : public QTreeWidgetItem {
 public:
  EntryListItem(Entry *);
  Entry *entry;
};

class EntryList : public QTreeWidget {
 public:
  EntryList(QWidget *parent = nullptr);
  void addEntryItem(Entry *);

 private:
  QList<EntryListItem *> m_entries;
};

#endif // ENTRYLIST_H