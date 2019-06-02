#include "manager.h"

Manager::Manager(Userdata data) { //从用户数据类获取用户信息
    name = data.usr;
    password = data.pwd;
    nickname = data.nickname;
    probnum = data.cp_num;
    level = data.level;
}

Manager::~Manager() {}

int Manager::get_usrtype() const { //用户类型
    return 1;
}

int Manager::get_probnum() const { //出题数目
    return probnum;
}

void Manager::inc_probnum() { //增加出题数目
    probnum++;
    if (probnum % 15 == 0) //每15道题增加一次等级
        inc_level();
    emit modifyed();
}
