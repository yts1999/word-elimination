#include "user.h"
#include <QSqlQuery>
#include <QVariant>

User::User() {}

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
    emit modifyed();
}
