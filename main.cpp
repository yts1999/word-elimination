#include "login_register.h"
#include "mainwindow.h"
#include "userdb.h"
#include "worddb.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    static UserDatabase userdb;
    static WordDatabase worddb;
    Login_Register lrw(nullptr, &userdb);
    MainWindow w(nullptr, &userdb);
    QObject::connect(&lrw, SIGNAL(toMainWindow(QString)), &w, SLOT(login_user(QString)));
    lrw.show();
    return a.exec();
}
