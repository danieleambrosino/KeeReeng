//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_DATABASE_H
#define KEEREENG_DATABASE_H

#include <QList>

class QFile;

class Crypto;
class Entry;

class Database {
 public:
  enum Error {
    NoError = 0,
    CorruptedDatabase,
    WrongPassword,
    FileNotWriteable,
    FileNotReadable,
  };

  Database();
  Database(const QString &filename, const QString &password);
  ~Database();

  void create(const QString &password, const QString &filename = "/tmp/__tmp.krdb");
  bool save();
  bool saveAs(const QString &filename);
  bool open();

  bool changePassword(const QString &old, const QString &newP);

  Error error() { return m_error; }
  QList<Entry *> entries;

 protected:
  bool lock();
  bool unlock();
  bool parseBin();
  bool checkPassword(const QString &password);

  Crypto *crypto;
  QFile *file;
  QByteArray binary;
  Error m_error;
  bool locked;
};

#endif //KEEREENG_DATABASE_H
