#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRegularExpression>
#include <stdio.h>
#include "Chesspiece.h"
#include "Chessboard.h"
#include "mydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setChesspieces();
    void set_round_counter();
    void set_turn_display();
    void set_color_display();
    void set_time_left();
    void set_Myovertime();
    void set_Opponentovertime();
    void set_give_up_button();
    void setPicture(QLabel *lable, QString path);
    void serverwrite(int x, int y, int a = -1);
    void clientwrite(int x, int y, int a = -1);
    bool check_IP(QString enterIP);

private:
    Ui::MainWindow *ui;
    MyDialog *dialog;
    QTcpServer *server = nullptr;
    QTcpSocket *serversocket = nullptr;
    QTcpSocket *clientsocket = nullptr;
    quint16 server_blocksize = 0;
    quint16 client_blocksize = 0;
    bool is_ready = false;

signals:
    void game_start();

public slots:
    void create_dialog1();
    void create_dialog2();
    void server_new_connection();
    void update_server();
    void update_client();
    void ready_to_write(int x = 0, int y = 0, int a = 0);
    void Disconnect();
};
#endif // MAINWINDOW_H
