#include "login_register.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    static UserDatabase userdb;
    Login_Register lrw(nullptr, &userdb);
    MainWindow w;
    QObject::connect(&lrw, SIGNAL(toMainWindow()), &w, SLOT(show()));
    lrw.show();
    return a.exec();
}
