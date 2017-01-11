//
// Created by daniele on 11/01/17.
//

#include <QTest>
#include <QCryptographicHash>

#include "core/Crypto.h"

class CryptoTest : public QObject {
  Q_OBJECT

 private slots:
  void constructAndValidateKey();
  void encryptionDecryptionTest();
};

void CryptoTest::constructAndValidateKey() {
  QByteArray key("prova");
  QVERIFY_EXCEPTION_THROWN(Crypto test(key), std::invalid_argument);

  key = "supercalifragilistichespiralitoso";
  QVERIFY_EXCEPTION_THROWN(Crypto test(key), std::invalid_argument);

  key = QCryptographicHash::hash(key, QCryptographicHash::Md5);
  Crypto test(key);
  Q_ASSERT(test.error() == test.NoError);
}

void CryptoTest::encryptionDecryptionTest() {
  Crypto test(QCryptographicHash::hash("prontoprova", QCryptographicHash::Md5));
  QByteArray source("really secret message");
  Q_DECL_NOTHROW(source);

  QByteArray result = test.encrypt(source);
  Q_DECL_NOTHROW(test.decrypt(result));
  QByteArray check = test.decrypt(result);
  Q_ASSERT(source == check);
  Q_ASSERT(test.error() == test.NoError);
}

QTEST_MAIN(CryptoTest)
#include "CryptoTest.moc"