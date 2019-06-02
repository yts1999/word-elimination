#include "player.h"

Player::Player() {}

Player::Player(Userdata data) { //从用户数据类获取用户信息
    name = data.usr;
    password = data.pwd;
    nickname = data.nickname;
    checknum = data.cp_num;
    exp = data.exp;
    level = data.level;
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
    emit modifyed();
}

void Player::add_exp(int delta) { //增加经验值
    exp += delta;
    if (exp / 100 > (exp - delta) / 100) //每100经验值增加一次用户等级
        inc_level();
    emit modifyed();
}
