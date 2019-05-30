#include "user.h"
#include <QSqlQuery>
#include <QVariant>

User::User(UserDatabase *_userdb, QString _name) : //初始化
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

QString User::get_name() const { //用户名
    return name;
}

QString User::get_nickname() const { //昵称
    return nickname;
}

int User::get_level() const { //等级
    return level;
}

void User::inc_level() { //增加等级
    level++;
    userdb->modify_level(name, level); //修改数据库信息
    emit modifyed();
}
