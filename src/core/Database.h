//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_DATABASE_H
#define KEEREENG_DATABASE_H

#include <QByteArray>

class QFile;

class Database {
 public:
  Database(const QString &filename, const QString &password);
  ~Database();

 private:
  QFile *file;
  QByteArray m_key;
};

#endif //KEEREENG_DATABASE_H
