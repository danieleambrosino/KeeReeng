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

  Database(const QString &filename, const QString &password);
  ~Database();

  bool save();
  bool open();

 private:
  bool encrypt();
  bool decrypt();
  bool parseBin();

  QList<Entry *> m_entries;
  QFile *file;
  QByteArray binary;
  Crypto *crypto;
  Error m_error;
  bool locked;
};

#endif //KEEREENG_DATABASE_H
