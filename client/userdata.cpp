#include "userdata.h"
#include "player.h"
#include "manager.h"

//该类用于向服务器发送或接受信息时使用

Userdata::Userdata(QString _usr, QString _pwd, QString _nickname, int _usrtype, int _cp_num, int _exp, int _level) : //初始化
    usr(_usr), pwd(_pwd), nickname(_nickname), usrtype(_usrtype), cp_num(_cp_num), exp(_exp), level(_level) {}

Userdata::Userdata(User *usr) { //从用户类获取用户数据
    this->usr = usr->get_name();
    pwd = "";
    nickname = usr->get_nickname();
    usrtype = usr->get_usrtype();
    level = usr->get_level();
    if (usrtype == 0) {
        cp_num = dynamic_cast<Player*>(usr)->get_checknum();
        exp = dynamic_cast<Player*>(usr)->get_exp();
    }
    else {
        cp_num = dynamic_cast<Manager*>(usr)->get_probnum();
    }
}
