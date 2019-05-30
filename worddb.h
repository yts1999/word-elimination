#ifndef WORDDB_H
#define WORDDB_H

#include <QSqlDatabase>

class WordDatabase : public QSqlDatabase {
public:
    WordDatabase();
    ~WordDatabase();
    bool check_word(const QString &word) const;
    void add_word(const QString &word);
    QString get_word() const;
    QString get_word(int level) const;
};

#endif // WORDDB_H
