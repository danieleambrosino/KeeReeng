//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_CRYPTO_H
#define KEEREENG_CRYPTO_H

#include <QByteArray>

class Crypto {
 public:
  enum Error {
    NoError,
    InvalidData,
    HashCheckFailed
  };

  explicit Crypto(const QByteArray &key);

  QByteArray encrypt(const QByteArray &bin);
  QByteArray decrypt(const QByteArray &bin);

  const Error &error() { return m_error; }

 private:
  QByteArray m_key;
  Error m_error;
};

#endif //KEEREENG_CRYPTO_H
