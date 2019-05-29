#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "player.h"
#include "worddb.h"
#include <QDialog>
#include <QTimer>

namespace Ui {
class Gamewindow;
}

class Gamewindow : public QDialog {
    Q_OBJECT

public:
    explicit Gamewindow(QWidget *parent = nullptr, WordDatabase *_worddb = nullptr);
    ~Gamewindow();
    void init(Player *_player);

private slots:
    void on_pushButton_clicked();
    void progress_switch();
    void word_switch();

private:
    void game_begin();
    Ui::Gamewindow *ui;
    Player *player;
    int show_timer_value, wait_timer_value;
    QTimer show_timer, wait_timer;
    int word_counter, word_counter_limit;
    WordDatabase *worddb;
    QString word;
};

#endif // GAMEWINDOW_H
