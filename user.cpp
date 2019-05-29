#include "user.h"
#include <QSqlQuery>
#include <QVariant>

User::User(UserDatabase *_userdb, QString _name) :
    userdb(_userdb), name(_name) {
    QSqlQuery userdb_query(*userdb);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(name));
    if (! userdb_query.first())
        return;
    password = userdb_query.value(1).toString();
    nickname = userdb_query.value(2).toString();
    level = userdb_query.value(6).toInt();
}

User::~User() {}

QString User::get_name() const {
    return name;
}

QString User::get_nickname() const {
    return nickname;
}

int User::get_level() const {
    return level;
}

void User::inc_level() {
    level++;
    userdb->modify_level(name, level);
    emit modifyed();
}
