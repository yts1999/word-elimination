#include "login_register.h"
#include "mainwindow.h"
#include "client.h"
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    srand(time(nullptr));
    static Client client;
    Login_Register lrw(nullptr, &client);
    MainWindow w(nullptr, &client);
    QObject::connect(&lrw, SIGNAL(toMainWindow(QString)), &w, SLOT(login_user(QString)));
    lrw.show();
    return a.exec();
}
