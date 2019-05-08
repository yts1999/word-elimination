#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"

class Manager : public User {
public:
    Manager();
    int get_probnum() const;
    void inc_probnum();

private:
    int probnum;
};

#endif // MANAGER_H
