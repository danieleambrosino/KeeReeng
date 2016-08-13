//
// Created by daniele on 13/08/16.
//

#include "Database.h"

#include <QFile>
#include <QCryptographicHash>

#include "Crypto.h"

Database::Database(const QString &filename, const QString &password) :
    file(new QFile(filename)),
    crypto(new Crypto(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5))),
    locked(true) {}

Database::~Database() {
  delete file;
  delete crypto;
}
