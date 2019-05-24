#include "player.h"
#include <QVariant>
#include <QSqlQuery>

Player::Player(const QString &_name , const QString &_password, const QString &_nickname, const int &_checknum, const int &_exp, const int &_level) :
    User(_name, _password, _nickname, _level), checknum(_checknum), exp(_exp) {}

Player::Player(UserDatabase *userdb, const QString &_name):
    User(_name, "", "", 1), checknum(0), exp(0) {
    QSqlQuery userdb_query(*userdb);
    userdb_query.exec(QString("select * from user where name=='%1'").arg(name));
    if (! userdb_query.first())
        return;
    password = userdb_query.value(1).toString();
    nickname = userdb_query.value(2).toString();
    checknum = userdb_query.value(4).toInt();
    exp = userdb_query.value(5).toInt();
    level = userdb_query.value(6).toInt();
}

Player::~Player() {}

int Player::get_usrtype() const {
    return 0;
}

int Player::get_checknum() const {
    return checknum;
}

int Player::get_exp() const {
    return exp;
}

void Player::inc_checknum() {
    checknum++;
}

void Player::add_exp(int delta) {
    exp += delta;
}
