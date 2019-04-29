#include "login.h"
#include "userdb.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    userdb_init();
    Login w;
    w.show();
    return a.exec();
}
