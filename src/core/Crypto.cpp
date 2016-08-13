//
// Created by daniele on 13/08/16.
//

#include "Crypto.h"

#include <QString>
#include <QCryptographicHash>

Crypto::Crypto(const QString &password) :
    m_key(QCryptographicHash::hash(password.toUtf8(),
                                   QCryptographicHash::Md5)) {}


