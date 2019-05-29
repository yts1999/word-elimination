#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "manager.h"
#include <QDesktopWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, UserDatabase *_userdb, WordDatabase *_worddb) :
    QMainWindow(parent), ui(new Ui::MainWindow), userdb(_userdb), player_model(this, *_userdb), manager_model(this, *_userdb), addword(nullptr, _worddb), gw(nullptr, _worddb) {
    ui->setupUi(this);
    setFixedSize(800, 600);
    move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 2);
    player_model.setTable("user");
    player_model.setFilter("type == 0");
    player_model.removeColumn(1);
    player_model.removeColumn(2);
    player_model.setHeaderData(0, Qt::Horizontal, "用户名");
    player_model.setHeaderData(1, Qt::Horizontal, "昵称");
    player_model.setHeaderData(2, Qt::Horizontal, "挑战关卡数");
    player_model.setHeaderData(3, Qt::Horizontal, "经验值");
    player_model.setHeaderData(4, Qt::Horizontal, "等级");
    player_model.setSort(0, Qt::AscendingOrder);
    ui->player_table->setModel(&player_model);
    for (int i = 0; i < 5; i++) {
        ui->player_table->setColumnWidth(i, 120);
        ui->player_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
    manager_model.setTable("user");
    manager_model.setFilter("type == 1");
    manager_model.removeColumn(1);
    manager_model.removeColumn(2);
    manager_model.removeColumn(3);
    manager_model.setHeaderData(0, Qt::Horizontal, "用户名");
    manager_model.setHeaderData(1, Qt::Horizontal, "昵称");
    manager_model.setHeaderData(2, Qt::Horizontal, "出题数");
    manager_model.setHeaderData(3, Qt::Horizontal, "等级");
    manager_model.setSort(0, Qt::AscendingOrder);
    ui->manager_table->setModel(&manager_model);
    for (int i = 0; i < 4; i++) {
        ui->manager_table->setColumnWidth(i, 150);
        ui->manager_table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }
    addword.hide();
    gw.hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::login_user(QString usrname) {
    if (userdb->get_usr_type(usrname) == 0) {
        user = new Player(userdb, usrname);
        ui->tabWidget->removeTab(1);
    }
     else {
        user = new Manager(userdb, usrname);
        ui->tabWidget->removeTab(0);
    }
    connect(user, SIGNAL(modifyed()), this, SLOT(refresh_userinfo()));
    refresh_userinfo();
    show();
}

void MainWindow::refresh_userinfo() {
    if (user->get_usrtype() == 0)
        ui->user_info->setText(QString("欢迎您，闯关者%1！挑战关卡数：%2　经验值：%3　等级：%4").arg(user->get_nickname()).arg(dynamic_cast<Player*>(user)->get_checknum()).arg(dynamic_cast<Player*>(user)->get_exp()).arg(user->get_level()));
     else
        ui->user_info->setText(QString("欢迎您，出题者%1！出题数：%2　等级：%3").arg(user->get_nickname()).arg(dynamic_cast<Manager*>(user)->get_probnum()).arg(user->get_level()));
}

void MainWindow::on_player_queryButton_clicked() {
    if (ui->player_select_checkBox->isChecked()) {
        int property = ui->player_select_property->currentIndex();
        QString field = ui->player_select_field->text();
        switch (property) {
        case 0:
            player_model.setFilter(QString("type == 0 and name == '%1'").arg(field));
            break;

        case 1:
            player_model.setFilter(QString("type == 0 and nickname == '%1'").arg(field));
            break;

        case 2:
            player_model.setFilter(QString("type == 0 and cp_num == '%1'").arg(field));
            break;

        case 3:
            player_model.setFilter(QString("type == 0 and exp == '%1'").arg(field));
            break;

        case 4:
            player_model.setFilter(QString("type == 0 and level == '%1'").arg(field));
        }
    }
    else
        player_model.setFilter("type == 0");
    player_model.select();
}

void MainWindow::on_manager_queryButton_clicked() {
    if (ui->manager_select_checkBox->isChecked()) {
        int property = ui->manager_select_property->currentIndex();
        QString field = ui->manager_select_field->text();
        switch (property) {
        case 0:
            manager_model.setFilter(QString("type == 1 and name == '%1'").arg(field));
            break;

        case 1:
            manager_model.setFilter(QString("type == 1 and nickname == '%1'").arg(field));
            break;

        case 2:
            manager_model.setFilter(QString("type == 1 and cp_num == '%1'").arg(field));
            break;

        case 3:
            manager_model.setFilter(QString("type == 1 and level == '%1'").arg(field));

        }
    }
    else
        manager_model.setFilter("type == 1");
    manager_model.select();
}

void MainWindow::on_player_select_checkBox_stateChanged(int arg1) {
    switch (arg1) {
    case (Qt::Unchecked):
        ui->player_select_property->setEnabled(false);
        ui->player_select_field->setEnabled(false);
        break;

    case (Qt::Checked):
        ui->player_select_property->setEnabled(true);
        ui->player_select_field->setEnabled(true);

    }
}

void MainWindow::on_manager_select_checkBox_stateChanged(int arg1) {
    switch (arg1) {
    case (Qt::Unchecked):
        ui->manager_select_property->setEnabled(false);
        ui->manager_select_field->setEnabled(false);
        break;

    case (Qt::Checked):
        ui->manager_select_property->setEnabled(true);
        ui->manager_select_field->setEnabled(true);

    }
}

void MainWindow::on_addwordButton_clicked() {
    addword.set_manager(dynamic_cast<Manager*>(user));
    addword.show();
}

void MainWindow::on_gameButton_clicked() {
    gw.init(dynamic_cast<Player*>(user));
    gw.show();
}
