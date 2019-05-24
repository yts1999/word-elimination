#ifndef WORDDB_H
#define WORDDB_H

#include <QSqlDatabase>

class WordDatabase : public QSqlDatabase {
public:
    WordDatabase();
    ~WordDatabase();
    void add_word(const QString &word);
};

#endif // WORDDB_H
