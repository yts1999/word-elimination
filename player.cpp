#include "player.h"
#include <QVariant>
#include <QSqlQuery>

Player::Player(UserDatabase *_userdb, QString _name): //从数据库中根据用户名查询用户信息
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

int Player::get_usrtype() const { //用户类型
    return 0;
}

int Player::get_checknum() const { //闯关数目
    return checknum;
}

int Player::get_exp() const { //经验值
    return exp;
}

void Player::inc_checknum() { //增加闯关数目
    checknum++;
    userdb->modify_cp_num(name, checknum); //修改数据库信息
    emit modifyed();
}

void Player::add_exp(int delta) { //增加经验值
    exp += delta;
    userdb->modify_exp(name, exp); //修改数据库信息
    emit modifyed();
}
