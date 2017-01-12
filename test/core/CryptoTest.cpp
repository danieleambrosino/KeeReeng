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
  void keyHashingTest();
};

void CryptoTest::constructAndValidateKey() {
  QByteArray key("prova");
  Crypto *test;
  QVERIFY_EXCEPTION_THROWN(test = new Crypto(key), std::invalid_argument);

  key = "supercalifragilistichespiralitoso";
  QVERIFY_EXCEPTION_THROWN(test = new Crypto(key), std::invalid_argument);

  key = QCryptographicHash::hash(key, QCryptographicHash::Md5);
  test = new Crypto(key);
  Q_ASSERT(test->error() == test->NoError);
  delete test;
}

void CryptoTest::encryptionDecryptionTest() {
  Crypto test(QCryptographicHash::hash("prontoprova", QCryptographicHash::Md5));
  QByteArray source("really secret message");

  QByteArray destination = test.encrypt(source);
  Q_DECL_NOTHROW(test.decrypt(destination));
  QByteArray check = test.decrypt(destination);
  Q_ASSERT(source == check);
  Q_ASSERT(test.error() == test.NoError);

  destination = "let's corrupt the data";
  test.decrypt(destination);
  Q_ASSERT(test.error() == test.HashCheckFailed);

  destination = "let's corrupt";
  test.decrypt(destination);
  Q_ASSERT(test.error() == test.InvalidData);
}

void CryptoTest::keyHashingTest() {
  QByteArray key = QCryptographicHash::hash("password", QCryptographicHash::Md5);
  Crypto *test;

  Q_DECL_NOTHROW(test = new Crypto(key));
  QVERIFY_EXCEPTION_THROWN(test->setKey("corruptedkey"),std::invalid_argument);
}

QTEST_MAIN(CryptoTest)
#include "CryptoTest.moc"