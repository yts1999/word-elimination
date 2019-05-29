#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"
#include <userdb.h>

class Player : public User {
    Q_OBJECT

public:
    //Player(UserDatabase *_userdb = nullptr, QString _name = "", QString _password = "", QString _nickname = "", int _checknum = 0, int _exp = 0, int _level = 1);
    Player(UserDatabase *_userdb = nullptr, QString _name = "");
    ~Player();
    int get_usrtype() const;
    int get_checknum() const;
    int get_exp() const;
    void inc_checknum();
    void add_exp(int delta);

private:
    int checknum, exp;
};

#endif // PLAYER_H
