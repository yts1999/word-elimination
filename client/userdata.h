#ifndef USERDATA_H
#define USERDATA_H

#include "user.h"
#include <QString>

class Userdata {
public:
    Userdata(QString _usr = "", QString _pwd = "", QString _nickname = "", int _usrtype = 0, int _cp_num = 0, int _exp = 0, int _level = 1);
    Userdata(User *usr);
    QString usr, pwd, nickname;
    int usrtype, cp_num, exp, level;
};

#endif // USERDATA_H
