#include "login_register.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    static UserDatabase userdb;
    Login_Register w(nullptr, &userdb);
    w.show();
    return a.exec();
}
