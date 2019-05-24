#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"
#include "userdb.h"

class Manager : public User {
public:
    Manager(const QString &_name = "", const QString &_password = "", const QString &_nickname = "", const int &_probnum = 0, const int &_level = 1);
    Manager(UserDatabase *userdb, const QString &_name);
    ~Manager();
    int get_usrtype() const;
    int get_probnum() const;
    void inc_probnum();

private:
    int probnum;
};

#endif // MANAGER_H
