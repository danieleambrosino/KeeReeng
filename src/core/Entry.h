//
// Created by daniele on 13/08/16.
//

#ifndef KEEREENG_ENTRY_H
#define KEEREENG_ENTRY_H

#include <QString>

struct Entry {
  Entry(const QString &m_title,
        const QString &m_username,
        const QString &m_password) :
      title(m_title), username(m_username), password(m_password) {}

  explicit Entry(const Entry *item) :
      title(item->title), username(item->username), password(item->password) {}

  QString title;
  QString username;
  QString password;
};

#endif //KEEREENG_ENTRY_H
