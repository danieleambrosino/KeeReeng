//
// Created by daniele on 14/08/16
//

#include "EntryList.h"

#include "core/Entry.h"
#include "core/Database.h"

#define PASSWORD "**********"

EntryListItem::EntryListItem(Entry *entry) :
    QTreeWidgetItem(QStringList() << entry->title << entry->username << PASSWORD),
    entryData(entry) {}

EntryList::EntryList(QWidget *parent) :
    QTreeWidget(parent),
    db(new Database) {}

void EntryList::addEntryItem(Entry *entry) {
  db->addEntry(entry);

  EntryListItem *item = new EntryListItem(entry);
  m_entries.append(item);

  updateList();
}

void EntryList::updateList() {
  clear();
  for (const auto &i : m_entries)
    addTopLevelItem(i);
}

void EntryList::create(const QString &password) {
  db->create(password);
}
