#ifndef WORDDB_H
#define WORDDB_H

#include <QSqlDatabase>

class WordDatabase : public QSqlDatabase {
public:
    WordDatabase();
    ~WordDatabase();
    void add_word(const QString &word);
    QString get_word() const;
};

#endif // WORDDB_H
