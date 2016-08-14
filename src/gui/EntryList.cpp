#include "EntryList.h"

EntryListItem::EntryListItem(QTreeWidget *view) : QTreeWidgetItem(view) {

}

EntryList::EntryList(QWidget *parent) :
    QTreeWidget(parent) {}
