#ifndef USER_H
#define USER_H

#include "userdb.h"
#include <QObject>
#include <QString>

class User : public QObject {
    Q_OBJECT

public:
    User(UserDatabase *_userdb = nullptr, QString _name = "");
    ~User();
    QString get_name() const;
    QString get_nickname() const;
    virtual int get_usrtype() const = 0;
    int get_level() const;
    void inc_level();

signals:
    void modifyed();

protected:
    UserDatabase *userdb;
    QString name, password, nickname;
    int level;
};

#endif // USER_H
