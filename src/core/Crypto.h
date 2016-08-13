//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_CRYPTO_H
#define KEEREENG_CRYPTO_H

#include <QByteArray>

class Crypto {
 public:
  explicit Crypto(const QString &password);

  QByteArray encrypt(const QByteArray &bin);
  QByteArray decrypt(const QByteArray &bin);

  bool hashCheckFailed() { return m_hashCheckFailed; }

 private:
  QByteArray m_key;
  bool m_hashCheckFailed;
};

#endif //KEEREENG_CRYPTO_H
