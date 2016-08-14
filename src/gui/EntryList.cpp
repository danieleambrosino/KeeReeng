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

void EntryListItem::update() {
  setText(0, entryData->title);
  setText(1, entryData->username);
}

EntryList::EntryList(QWidget *parent) :
    QTreeWidget(parent),
    db(new Database) {}

void EntryList::addEntryItem(Entry *entry) {
  db->entries.append(entry);
  EntryListItem *item = new EntryListItem(entry);

  m_entries.append(item);
  updateList();
}

void EntryList::updateList() {
  for (const auto &i : m_entries) {
    addTopLevelItem(i);
    i->update();
  }
}

void EntryList::create(const QString &password, const QString &filename) {
  db->create(password, filename);
}
