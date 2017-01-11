//
// Created by daniele on 11/01/17.
//

#include <QTest>
#include <QObject>

class DatabaseTest : public QObject {
  Q_OBJECT

 private slots:
  void saveAndOpenDB();
};

void DatabaseTest::saveAndOpenDB() {

}

#include "DatabaseTest.moc"