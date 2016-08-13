//
// Created by daniele on 13/08/16.
//

#include "Crypto.h"

#include <QString>
#include <QCryptographicHash>

#define MD5_SIZE  16
#define SHA1_SIZE 20

Crypto::Crypto(const QString &password) :
    m_key(QCryptographicHash::hash(password.toUtf8(),
                                   QCryptographicHash::Md5)),
    m_error(NoError) {}

QByteArray Crypto::encrypt(const QByteArray &bin) {
  QByteArray tmp = bin;

  tmp.prepend(QCryptographicHash::hash(bin, QCryptographicHash::Sha1));

  int pos(0), size(bin.size());
  char last(0);

  while (pos < size) {
    tmp[pos] = tmp.at(pos) ^ m_key.at(pos % MD5_SIZE) ^ last;
    last = tmp.at(pos);
    ++pos;
  }

  return tmp;
}
