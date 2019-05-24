#ifndef USER_H
#define USER_H

#include "userdb.h"
#include <QString>

class User {
public:
    User(const QString &_name = "", const QString &_password = "", const QString &_nickname = "", const int &_level = 1);
    virtual ~User();
    QString get_name() const;
    QString get_nickname() const;
    virtual int get_usrtype() const = 0;
    int get_level() const;
    void inc_level();

protected:
    QString name, password, nickname;
    int level;
};

#endif // USER_H
