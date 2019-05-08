#include "player.h"

Player::Player(const QString &_name , const QString &_password, const QString &_nickname, const int &_level, const int &_checknum, const int &_exp) :
    User(_name, _password, _nickname, _level), checknum(_checknum), exp(_exp) {}

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
