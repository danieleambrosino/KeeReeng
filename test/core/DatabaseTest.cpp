//
// Created by daniele on 11/01/17.
//

#include <QTest>
#include <QObject>
#include <core/Database.h>

class DatabaseTest : public QObject {
  Q_OBJECT

 private slots:
  void saveAndOpenDB();
};

void DatabaseTest::saveAndOpenDB() {
  Database database;
  database.create("password");
  Q_ASSERT(database.save() == true);
  Q_ASSERT(database.error() == database.NoError);


}

QTEST_MAIN(DatabaseTest)
#include "DatabaseTest.moc"