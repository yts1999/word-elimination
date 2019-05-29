#include "worddb.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>

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

QString WordDatabase::get_word() const {
    QSqlQuery worddb_query(*this);
    worddb_query.exec("select count(*) from word");
    if (! worddb_query.first())
        return "";
    int cnt = worddb_query.value(0).toInt();
    int id = rand() % cnt + 1;
    worddb_query.exec(QString("select * from word where rowid == '%1'").arg(id));
    if (! worddb_query.first())
        return "";
    return worddb_query.value(0).toString();
}
