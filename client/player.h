#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"
#include "userdata.h"

class Player : public User {
    Q_OBJECT

public:
    Player();
    Player(Userdata data);
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
