#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>

Gamewindow::Gamewindow(QWidget *parent, WordDatabase *_worddb) :
    QDialog(parent), ui(new Ui::Gamewindow), player(nullptr), show_timer_value(0), wait_timer_value(0), word_counter(0), word_counter_limit(0), worddb(_worddb) {
    ui->setupUi(this);
    show_timer.setSingleShot(true);
    wait_timer.setSingleShot(true);
    connect(&show_timer, SIGNAL(timeout()), this, SLOT(progress_switch()));
    connect(&wait_timer, SIGNAL(timeout()), this, SLOT(word_switch()));
    connect(ui->wordInput, SIGNAL(returnPressed()), this, SLOT(word_switch()));
}

Gamewindow::~Gamewindow() {
    delete ui;
}

void Gamewindow::init(Player *_player) {
    player = _player;
    ui->level->setText(QString("第%1关").arg(player->get_checknum() + 1));
    word_counter = 0;
    word_counter_limit = 5;
    show_timer_value = 2;
    wait_timer_value = 2;
    game_begin();
}

void Gamewindow::on_pushButton_clicked() {
    show_timer.stop();
    wait_timer.stop();
    hide();
}

void Gamewindow::progress_switch() {
    show_timer.stop();
    int val = ui->progressBar->value() - 100 / show_timer_value;
    if (val < show_timer_value)
        val = 0;
    ui->progressBar->setValue(val);
    if (val == 0) {
        ui->word_show->hide();
        ui->wordInput->setEnabled(true);
        ui->wordInput->setFocus();
        wait_timer.start(wait_timer_value * 1000);
    }
    else
        show_timer.start(1000);
}

void Gamewindow::word_switch() {
    wait_timer.stop();
    if (ui->wordInput->text() != ui->word_show->text()) {
        QMessageBox::critical(this, "失败", "闯关失败！");
        hide();
        return;
    }
    word_counter++;
    if (word_counter == word_counter_limit) {
        QMessageBox::information(this, "成功", "闯关成功！");
        player->inc_checknum();
        hide();
        return;
    }
    game_begin();
}

void Gamewindow::game_begin() {
    ui->wordInput->clear();
    ui->wordInput->setEnabled(false);
    ui->word_show->setText(worddb->get_word());
    ui->word_show->show();
    ui->progressBar->setValue(100);
    show_timer.start(1000);
}
