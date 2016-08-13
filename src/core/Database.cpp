//
// Created by daniele on 13/08/16.
//

#include "Database.h"

#include <QFile>
#include <QtCore/QCryptographicHash>

Database::Database(const QString &filename, const QString &password) :
    file(new QFile(filename)),
    m_key(QCryptographicHash::hash(password, QCryptographicHash::Md5)) {}

Database::~Database() {
  delete file;
}
