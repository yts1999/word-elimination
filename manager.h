#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"
#include "userdb.h"

class Manager : public User {
    Q_OBJECT

public:
    //Manager(UserDatabase *_userdb = nullptr, QString _name = "", QString _password = "", QString _nickname = "", int _probnum = 0, int _level = 1);
    Manager(UserDatabase *_userdb = nullptr, QString _name = "");
    ~Manager();
    int get_usrtype() const;
    int get_probnum() const;
    void inc_probnum();

private:
    int probnum;
};

#endif // MANAGER_H
