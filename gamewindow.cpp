#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>

Gamewindow::Gamewindow(QWidget *parent, WordDatabase *_worddb) :
    QDialog(parent), ui(new Ui::Gamewindow), player(nullptr), show_timer_value(0), wait_timer_value(0), word_counter(0), word_counter_limit(0), worddb(_worddb) {
    ui->setupUi(this);
    show_timer.setSingleShot(true);
    wait_timer.setSingleShot(true);
    connect(&show_timer, SIGNAL(timeout()), this, SLOT(progress_switch())); //显示定时器超时时切换进度条状态
    connect(&wait_timer, SIGNAL(timeout()), this, SLOT(word_switch())); //等待定时器超时时切换单词
    connect(ui->wordInput, SIGNAL(returnPressed()), this, SLOT(word_switch())); //按下回车时切换单词
}

Gamewindow::~Gamewindow() {
    delete ui;
}

void Gamewindow::init(Player *_player) { //用户信息及界面初始化
    player = _player;
    ui->level->setText(QString("第%1关").arg(player->get_checknum() + 1));
    word_counter = 0; //清空单词计数器
    word_counter_limit = 5; //设置单词数量、显示时间及输入时间
    show_timer_value = 2;
    wait_timer_value = 2;
    game_begin();
}

void Gamewindow::on_pushButton_clicked() {
    show_timer.stop(); //关闭定时器及窗口
    wait_timer.stop();
    hide();
}

void Gamewindow::progress_switch() {
    show_timer.stop();
    int val = ui->progressBar->value() - 100 / show_timer_value; //更新进度条
    if (val < show_timer_value)
        val = 0;
    ui->progressBar->setValue(val);
    if (val == 0) { //进度条读完，进入输入阶段
        ui->word_show->hide();
        ui->wordInput->setEnabled(true);
        ui->wordInput->setFocus();
        wait_timer.start(wait_timer_value * 1000);
    }
    else
        show_timer.start(1000); //设定1s的定时器
}

void Gamewindow::word_switch() {
    wait_timer.stop();
    if (ui->wordInput->text() != ui->word_show->text()) { //单词不匹配
        QMessageBox::critical(this, "失败", "闯关失败！");
        hide();
        return;
    }
    word_counter++; //单词匹配，单词计数器加1
    if (word_counter == word_counter_limit) { //本轮单词输入已经结束
        QMessageBox::information(this, "成功", "闯关成功！");
        player->inc_checknum(); //过关数增加
        hide();
        return;
    }
    game_begin();
}

void Gamewindow::game_begin() { //显示新的单词
    ui->wordInput->clear();
    ui->wordInput->setEnabled(false);
    ui->word_show->setText(worddb->get_word()); //从数据库获取一个单词
    ui->word_show->show();
    ui->progressBar->setValue(100);
    show_timer.start(1000);
}
