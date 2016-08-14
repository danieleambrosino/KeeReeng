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
    FileNotWritable,
    FileNotReadable,
  };

  Database();
  Database(const QString &filename, const QString &password);
  ~Database();

  void create(const QString &password);
  bool save();
  bool open();

  void addEntry(Entry *);

 private:
  bool encrypt();
  bool decrypt();
  bool parseBin();

  QFile *file;
  Crypto *crypto;
  QList<Entry *> m_entries;
  QByteArray binary;
  Error m_error;
  bool locked;
};

#endif //KEEREENG_DATABASE_H
