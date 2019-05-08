#include "user.h"

User::User(const QString &_name, const QString &_password, const QString &_nickname, const int &_level) :
    name(_name), password(_password), nickname(_nickname), level(_level) {}

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
}
