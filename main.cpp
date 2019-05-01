#include "login_register.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Login_Register w;
    w.show();
    return a.exec();
}
