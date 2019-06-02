#include "worddb.h"
#include <QSqlQuery>
#include <QVariant>
#include <iostream>

WordDatabase::WordDatabase() : //数据库初始化
    QSqlDatabase(addDatabase("QSQLITE", "worddb")) {
        setHostName("localhost");
        setDatabaseName("words.db");
        if (! open()) {
            std::cout << "Error! Database connection failed.\n";
            exit(1);
        }
        else {
            QSqlQuery worddb_create(*this);
            worddb_create.exec("create table word(spell varchar(100) primary key)");
        }
}

WordDatabase::~WordDatabase() {
    close();
    removeDatabase("worddb");
}

void WordDatabase::add_word(const QString &word) { //添加单词
    QSqlQuery worddb_query(*this);
    worddb_query.exec(QString("insert into word values('%1')").arg(word));
}

bool WordDatabase::check_word(const QString &word) const { //检查单词是否存在
    QSqlQuery worddb_query(*this);
    worddb_query.exec(QString("select * from word where spell=='%1'").arg(word));
    return worddb_query.first();
}

QString WordDatabase::get_word() const { //获取单词
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

QString WordDatabase::get_word(int level) const { //根据关卡号获取单词
    QSqlQuery worddb_query(*this);
    worddb_query.exec("select count(*) from word");
    if (! worddb_query.first())
        return "";
    int cnt = worddb_query.value(0).toInt();
    worddb_query.exec(QString("select * from word order by length(spell)"));
    if (! worddb_query.first())
        return "";
    int id = ((((level <= 20 ? level : 20) - (level > 2 ? 2 : level)) * cnt / 20) + rand() % (cnt / 10 + 1)) % cnt;
    worddb_query.seek(id);
    return worddb_query.value(0).toString();
}
