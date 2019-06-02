#include "server.h"
#include "userdb.h"
#include "worddb.h"
#include <QCoreApplication>
using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    static UserDatabase userdb;
    static WordDatabase worddb;
    Server s(&userdb, &worddb);
    return a.exec();
}
