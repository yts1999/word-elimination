#include "manager.h"

Manager::Manager(const QString &_name, const QString &_password, const QString &_nickname, const int &_level, const int &_probnum) :
    User(_name, _password, _nickname, _level), probnum(_probnum) {}

int Manager::get_probnum() const {
    return probnum;
}

void Manager::inc_probnum() {
    probnum++;
}
