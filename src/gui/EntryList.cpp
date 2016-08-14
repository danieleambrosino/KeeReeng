//
// Created by daniele on 14/08/16
//

#include "EntryList.h"

#include "core/Entry.h"
#include "core/Database.h"

#define PASSWORD "**********"

EntryListItem::EntryListItem(Entry *entry) :
    QTreeWidgetItem(QStringList() << entry->title() << entry->username() << PASSWORD),
    entry(entry) {}

EntryList::EntryList(QWidget *parent) :
    QTreeWidget(parent) {}

void EntryList::addEntryItem(Entry *entry) {
  db->addEntry(entry);
  EntryListItem *item = new EntryListItem(entry);
  m_entries.append(item);
  addTopLevelItem(item);
}
