//
// Created by daniele on 13/08/16.
//

#include "Crypto.h"

#include <QCryptographicHash>
#include <stdexcept>

enum ChecksumSize {
  MD5_SIZE = 16,
  SHA1_SIZE = 20
};

Crypto::Crypto(const QByteArray &key) :
    m_key(key),
    m_error(NoError) {
  if (m_key.size() != MD5_SIZE)
    throw std::invalid_argument(
        "Crypto::Crypto : fatal error: key size (MD5_SIZE) must be 16 byte");
}

QByteArray Crypto::encrypt(const QByteArray &bin) {
  QByteArray tmp = bin;

  tmp.prepend(QCryptographicHash::hash(bin, QCryptographicHash::Sha1));

  int pos(0), size(tmp.size());
  char last(0);

  while (pos < size) {
    tmp[pos] = tmp.at(pos) ^ m_key.at(pos % MD5_SIZE) ^ last;
    last = tmp.at(pos);
    ++pos;
  }

  m_error = NoError;
  return tmp;
}

QByteArray Crypto::decrypt(const QByteArray &bin) {
  if (bin.size() < SHA1_SIZE) {
    m_error = InvalidData;
    qWarning("Crypto::decrypt : invalid data");
    return QByteArray();
  }

  QByteArray tmp = bin;

  int pos(0), size(tmp.size());
  char last(0), current;

  while (pos < size) {
    current = tmp.at(pos);
    tmp[pos] = tmp.at(pos) ^ last ^ m_key.at(pos % MD5_SIZE);
    last = current;
    ++pos;
  }

  QByteArray checksum = tmp.left(SHA1_SIZE);
  tmp = tmp.mid(SHA1_SIZE);

  if (checksum != QCryptographicHash::hash(tmp, QCryptographicHash::Sha1)) {
    m_error = HashCheckFailed;
    qWarning("Crypto::decrypt : hash check failed (wrong password?)");
    return QByteArray();
  }

  m_error = NoError;
  return tmp;
}
