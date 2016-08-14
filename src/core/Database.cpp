//
// Created by daniele on 13/08/16.
//

#include "Database.h"

#include <QFile>
#include <QCryptographicHash>

#include "Crypto.h"
#include "Entry.h"

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

enum ItemFlag {
  ITEM_START = 0x01,
  ITEM_END = 0x02
};

Database::Database() :
    file(nullptr),
    crypto(nullptr) {}

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

void Database::create(const QString &password) {
  file = new QFile("/tmp/__tmp.krdb");
  crypto = new Crypto(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5));
}

bool Database::save() {
  if (not file->open(QFile::WriteOnly)) {
    m_error = FileNotWritable;
    qWarning("Database::save : Unable to write on file (unsufficient permissions?)");
    return false;
  }

  if (m_entries.isEmpty())
    qWarning("Database::save : Warning: empty database");

  for (const auto &i : m_entries)
    binary.append(ITEM_START + i->title + ITEM_END +
                  ITEM_START + i->username + ITEM_END +
                  ITEM_START + i->password + ITEM_END);

  if (not encrypt()) {
    qWarning("Database::save : Encryption failed!");
    return false;
  }

  file->write(binary);
  file->close();
  m_error = NoError;
  return true;
}

bool Database::open() {
  if (not file->open(QFile::ReadOnly)) {
    m_error = FileNotReadable;
    qWarning("Database::open : Unable to read file");
    return false;
  }

  binary = file->readAll();

  if (not decrypt()) {
    qWarning("Database::open : Decryption failed!");
    return false;
  }

  if (not parseBin()) {
    qWarning("Database::open : Database parsing failed!");
    return false;
  }

  file->close();
  return true;
}

bool Database::parseBin() {
  if (binary.isEmpty()) {
    qWarning("Database::parseBin : Nothing to parse...");
    return false;
  }

  int pos(0);
  const int size(binary.size());
  enum CurrentParse { t, u, p };

  QString title = "", username = "", password = "";
  QString *currentString = &title;
  CurrentParse currentParse = t;

  while (pos < size) {
    while ((pos < size) and (binary.at(pos) != ITEM_START)) { ++pos; }

    ++pos;
    while ((pos < size) and (binary.at(pos) != ITEM_END)) {
      currentString->append(binary.at(pos));
      ++pos;
    }

    switch (currentParse) {
      case t:
        currentParse = u;
        currentString = &username;
        break;
      case u:
        currentParse = p;
        currentString = &password;
        break;
      case p:
        m_entries.append(new Entry(title, username, password));
        title.clear();
        username.clear();
        password.clear();
        currentParse = t;
        currentString = &title;
        break;
    }
  }

  return true;
}

void Database::addEntry(Entry *item) {
  m_entries.append(new Entry(item));
}
