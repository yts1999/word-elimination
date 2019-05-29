#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"

class Player : public User {
    Q_OBJECT

public:
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
