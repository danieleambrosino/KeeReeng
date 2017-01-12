//
// Created by daniele on 11/01/17.
//

#include <QTest>

#include "core/Database.h"
#include "core/Entry.h"

class DatabaseTest : public QObject {
  Q_OBJECT

 private slots:
  void saveAndOpenDB();
  void changePasswordTest();
};

void DatabaseTest::saveAndOpenDB() {
  Database database;
  database.create("password");

  Entry *entry = new Entry("account", "username", "password");
  database.entries.push_back(entry);

  Q_ASSERT(database.save() == true);
  Q_ASSERT(database.error() == database.NoError);

  database.entries.clear();
  Q_ASSERT(database.open() == true);
  Q_ASSERT(database.error() == database.NoError);

  delete entry;
}

void DatabaseTest::changePasswordTest() {
  Database database;
  database.create("old_password");

  Q_ASSERT(database.changePassword("old_wrong_password", "new_password") == false);
  Q_ASSERT(database.changePassword("old_password", "new_password") == true);
}

QTEST_MAIN(DatabaseTest)
#include "DatabaseTest.moc"