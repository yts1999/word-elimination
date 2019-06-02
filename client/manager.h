#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"
#include "userdata.h"

class Manager : public User {
    Q_OBJECT

public:
    Manager();
    Manager(Userdata data);
    ~Manager();
    int get_usrtype() const;
    int get_probnum() const;
    void inc_probnum();

private:
    int probnum;
};

#endif // MANAGER_H
