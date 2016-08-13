//
// Created by daniele on 13/08/16.
//

#include "Database.h"

#include <QFile>
#include <QCryptographicHash>

#include "Crypto.h"

#define handleCryptoError(error) \
switch (error) { \
  case Crypto::NoError: \
    m_error = NoError; \
    break; \
  case Crypto::InvalidData: \
    m_error = CorruptedDatabase; \
    break; \
  case Crypto::HashCheckFailed: \
    m_error = WrongPassword; \
    break; \
}

Database::Database(const QString &filename, const QString &password) :
    file(new QFile(filename)),
    crypto(new Crypto(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5))),
    locked(true) {}

Database::~Database() {
  delete file;
  delete crypto;
}

bool Database::encrypt() {
  if (binary.isEmpty() or locked) {
    qWarning("Database::encrypt : nothing to encrypt...");
    return true;
  }

  binary = crypto->encrypt(binary);
  locked = (crypto->error() == Crypto::NoError);

  handleCryptoError(crypto->error());

  return locked;
}

bool Database::decrypt() {
  if (binary.isEmpty() or not locked) {
    qWarning("Database::decrypt : nothing to decrypt...");
    return true;
  }

  binary = crypto->decrypt(binary);
  if (crypto->error() == Crypto::NoError)
    locked = false;

  handleCryptoError(crypto->error());

  return not locked;
}
