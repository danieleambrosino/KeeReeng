//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_DATABASE_H
#define KEEREENG_DATABASE_H

#include <QByteArray>

class QFile;
class Crypto;

class Database {
 public:
  Database(const QString &filename, const QString &password);
  ~Database();

  bool save();
  bool open();

 private:
  bool encrypt();
  bool decrypt();

  QFile *file;
  Crypto *crypto;
};

#endif //KEEREENG_DATABASE_H
