//
// Created by daniele on 14/08/16
//

#include "EntryList.h"

#include "core/Entry.h"

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
  Database() {}

void EntryList::addItem(Entry *entry) {
  entries.append(entry);
  updateView();
}

void EntryList::updateView() {
  items.clear();
  QTreeWidget::clear();

  for (const auto &i : entries)
    items.push_back(new EntryListItem(i));

  for (const auto &i : items) {
    i->update();
    addTopLevelItem(i);
  }
}

void EntryList::clear() {
  entries.clear();
  items.clear();
  QTreeWidget::clear();
}
