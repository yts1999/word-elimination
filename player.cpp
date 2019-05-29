#include "player.h"
#include <QVariant>
#include <QSqlQuery>

Player::Player(UserDatabase *_userdb, QString _name):
    User(_userdb, _name), checknum(0), exp(0) {
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
    userdb->modify_cp_num(name, checknum);
    emit modifyed();
}

void Player::add_exp(int delta) {
    exp += delta;
    userdb->modify_exp(name, exp);
    emit modifyed();
}
