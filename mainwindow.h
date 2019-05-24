#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userdb.h"
#include "user.h"
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, UserDatabase *_userdb = nullptr);
    ~MainWindow();

private slots:
    void login_user(QString usrname);
    void refresh_userinfo();
    void on_player_queryButton_clicked();
    void on_manager_queryButton_clicked();
    void on_player_select_checkBox_stateChanged(int arg1);
    void on_manager_select_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    UserDatabase *userdb;
    QSqlTableModel player_model, manager_model;
    User *user;
};

#endif // MAINWINDOW_H
