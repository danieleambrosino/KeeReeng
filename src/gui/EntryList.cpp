#include "EntryList.h"

#include "../core/Entry.h"

#define PASSWORD "**********"

EntryListItem::EntryListItem(Entry *entry) :
    entry(entry),
    QTreeWidgetItem(QStringList() << entry->title() << entry->username() << PASSWORD) {}

EntryList::EntryList(QWidget *parent) :
    QTreeWidget(parent) {}

void EntryList::addEntryItem(Entry *entry) {
  EntryListItem *item = new EntryListItem(entry);
  m_entries.append(item);
  addTopLevelItem(item);
}
