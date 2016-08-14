#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include <QTreeWidget>

class Entry;

class EntryListItem : public QTreeWidgetItem {
  EntryListItem(QTreeWidget *);
  Entry *entry;
};

class EntryList : public QTreeWidget {
 public:
  EntryList(QWidget *parent = nullptr);

 private:
  QList<EntryListItem *> m_entries;
};

#endif // ENTRYLIST_H