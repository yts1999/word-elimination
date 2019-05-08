#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"

class Player : public User {
public:
    Player(const QString &_name = "", const QString &_password = "", const QString &_nickname = "", const int &_level = 1, const int &_checknum = 0, const int &_exp = 0);
    int get_checknum() const;
    int get_exp() const;
    void inc_checknum();
    void add_exp(int delta);

private:
    int checknum, exp;
};

#endif // PLAYER_H
