#include "worddb.h"
#include <QMessageBox>
#include <QSqlQuery>

WordDatabase::WordDatabase() :
    QSqlDatabase(addDatabase("QSQLITE", "worddb")) {
        setHostName("localhost");
        setDatabaseName("words.db");
        if (! open())
            QMessageBox::critical(nullptr, "错误", "连接错误！");
        else {
            QSqlQuery worddb_create(*this);
            worddb_create.exec("create table word(spell varchar(100) primary key)");
        }
}

WordDatabase::~WordDatabase() {
    close();
    removeDatabase("worddb");
}

void WordDatabase::add_word(const QString &word) {
    QSqlQuery worddb_query(*this);
    worddb_query.exec(QString("insert into word values('%1')").arg(word));
}
