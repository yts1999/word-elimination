#include "player.h"

Player::Player() {}

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
