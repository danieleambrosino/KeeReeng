//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_ENTRY_H
#define KEEREENG_ENTRY_H

#include <QString>

class Entry {
 public:
  Entry(const QString &m_title,
        const QString &m_username,
        const QString &m_password) :
      m_title(m_title), m_username(m_username), m_password(m_password) {}

  explicit Entry(const Entry *item) :
      m_title(item->title()), m_username(item->username()), m_password(item->password()) {}

  const QString &title() const { return m_title; }
  const QString &username() const { return m_username; }
  const QString &password() const { return m_password; }

  void setTitle(const QString &title) { Entry::m_title = title; }
  void setUsername(const QString &username) { Entry::m_username = username; }
  void setPassword(const QString &password) { Entry::m_password = password; }

 private:
  QString m_title;
  QString m_username;
  QString m_password;
};

#endif //KEEREENG_ENTRY_H
