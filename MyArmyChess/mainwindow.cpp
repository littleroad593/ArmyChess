#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPicture(ui->chessboard, ":/new/prefix1/png/kongqipan.png");
    setChesspieces();
    set_round_counter();
    set_turn_display();
    set_color_display();
    set_time_left();
    set_Myovertime();
    set_Opponentovertime();
    set_give_up_button();
    ui->centralwidget->setRailway();

    QObject::connect(ui->centralwidget->give_up_button, &QPushButton::clicked, ui->centralwidget, &Chessboard::give_up);
    QObject::connect(ui->actionCreate, &QAction::triggered, this, &MainWindow::create_dialog1);
    QObject::connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::create_dialog2);
    QObject::connect(ui->centralwidget, &Chessboard::has_clicked, this, &MainWindow::ready_to_write);
    QObject::connect(ui->actionStart, &QAction::triggered, this, [&](){
        if(ui->centralwidget->has_connected)
        {
            if(!(serversocket && is_ready))
                ready_to_write();
            is_ready = true;
        }//联机开始操作
        else
        {
            ui->centralwidget->set_first_turn();
            emit game_start();
        }//单机开始操作
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPicture(QLabel *label, QString path)
{
    QPixmap *pixmap = new QPixmap(path);
    pixmap->scaled(label->size(), Qt::KeepAspectRatio);
    label->setScaledContents(true);
    label->setPixmap(*pixmap);
}//图片自适应Label函数

void MainWindow::setChesspieces()
{
    QList<Chesspiece*> labelList = ui->centralwidget->findChildren<Chesspiece*>();
    for (int i = 0; i < labelList.size(); i++)
    {
        Chesspiece *chesspiece = labelList.at(i);
        setPicture(chesspiece, ":/new/prefix1/png/weizhi.png");
        chesspiece->setVisible(false);
        ui->centralwidget->chesspieces.push_back(chesspiece);
    }

    QObject::connect(this, &MainWindow::game_start, ui->centralwidget, [&](){
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_8->setVisible(true);
        ui->label_9->setVisible(true);
        ui->label_10->setVisible(true);
        ui->label_11->setVisible(true);
        ui->label_12->setVisible(true);
        ui->label_13->setVisible(true);
        ui->label_14->setVisible(true);
        ui->label_15->setVisible(true);
        ui->label_16->setVisible(true);
        ui->label_17->setVisible(true);
        ui->label_18->setVisible(true);
        ui->label_19->setVisible(true);
        ui->label_20->setVisible(true);
        ui->label_21->setVisible(true);
        ui->label_22->setVisible(true);
        ui->label_23->setVisible(true);
        ui->label_24->setVisible(true);
        ui->label_25->setVisible(true);
        ui->label_26->setVisible(true);
        ui->label_27->setVisible(true);
        ui->label_28->setVisible(true);
        ui->label_29->setVisible(true);
        ui->label_30->setVisible(true);
        ui->label_31->setVisible(true);
        ui->label_32->setVisible(true);
        ui->label_33->setVisible(true);
        ui->label_34->setVisible(true);
        ui->label_35->setVisible(true);
        ui->label_36->setVisible(true);
        ui->label_37->setVisible(true);
        ui->label_38->setVisible(true);
        ui->label_39->setVisible(true);
        ui->label_40->setVisible(true);
        ui->label_41->setVisible(true);
        ui->label_42->setVisible(true);
        ui->label_43->setVisible(true);
        ui->label_44->setVisible(true);
        ui->label_45->setVisible(true);
        ui->label_46->setVisible(true);
        ui->label_47->setVisible(true);
        ui->label_48->setVisible(true);
        ui->label_49->setVisible(true);
        ui->label_50->setVisible(true);
        ui->centralwidget->round_counter->setVisible(true);
        ui->centralwidget->color_display->setVisible(true);
        ui->centralwidget->time_left->setVisible(true);
        ui->centralwidget->Myovertime->setVisible(true);
        ui->centralwidget->Opponentovertime->setVisible(true);
        ui->centralwidget->start = true;
        if(serversocket)
        {
            int a = ui->centralwidget->set_first_turn();
            ready_to_write(0, 0, a);
        }
    });
}//设置棋子

void MainWindow::set_round_counter()
{
    ui->centralwidget->round_counter = new QLabel(this);
    ui->centralwidget->round_counter->setGeometry(600, 50, 200, 30);
    QFont font;
    font.setPointSize(15);
    ui->centralwidget->round_counter->setFont(font);
    ui->centralwidget->round_counter->setText("Round: 0");
    ui->centralwidget->round_counter->setVisible(false);
}//设置轮次计数器标签

void MainWindow::set_turn_display()
{
    ui->centralwidget->turn_display = new QLabel(this);
    ui->centralwidget->turn_display->setGeometry(600, 80, 200, 30);
    QFont font;
    font.setPointSize(15);
    ui->centralwidget->turn_display->setFont(font);
    ui->centralwidget->turn_display->setVisible(false);
}//设置回合标签

void MainWindow::set_color_display()
{
    ui->centralwidget->color_display = new QLabel(this);
    ui->centralwidget->color_display->setGeometry(600, 110, 200, 30);
    QFont font;
    font.setPointSize(15);
    ui->centralwidget->color_display->setFont(font);
    ui->centralwidget->color_display->setText("我的颜色: ");
    ui->centralwidget->color_display->setVisible(false);
}//设置我方颜色标签

void MainWindow::set_time_left()
{
    ui->centralwidget->time_left = new QLabel(this);
    ui->centralwidget->time_left->setGeometry(600, 240, 200, 30);
    QFont font;
    font.setPointSize(15);
    ui->centralwidget->time_left->setFont(font);
    ui->centralwidget->time_left->setText("步时剩余: 20秒");
    ui->centralwidget->time_left->setVisible(false);
}//设置剩余步时标签

void MainWindow::set_Myovertime()
{
    ui->centralwidget->Myovertime = new QLabel(this);
    ui->centralwidget->Myovertime->setGeometry(600, 140, 200, 30);
    QFont font;
    font.setPointSize(15);
    ui->centralwidget->Myovertime->setFont(font);
    ui->centralwidget->Myovertime->setText("我方超时: 0次");
    ui->centralwidget->Myovertime->setVisible(false);
}//设置我方超时次数标签

void MainWindow::set_Opponentovertime()
{
    ui->centralwidget->Opponentovertime = new QLabel(this);
    ui->centralwidget->Opponentovertime->setGeometry(600, 170, 200, 30);
    QFont font;
    font.setPointSize(15);
    ui->centralwidget->Opponentovertime->setFont(font);
    ui->centralwidget->Opponentovertime->setText("对方超时: 0次");
    ui->centralwidget->Opponentovertime->setVisible(false);
}//设置对方超时次数标签

void MainWindow::set_give_up_button()
{
    ui->centralwidget->give_up_button = new QPushButton(this);
    ui->centralwidget->give_up_button->setGeometry(600, 600, 50, 30);
    ui->centralwidget->give_up_button->setText("认输");
    ui->centralwidget->give_up_button->setVisible(false);
    ui->centralwidget->give_up_button->setEnabled(false);
}//设置认输按钮

void MainWindow::create_dialog1()
{
    dialog = new MyDialog(this);
    dialog->setWindowTitle("创建服务器");
    dialog->create_server_window();
    dialog->show();
    if(dialog->exec() == MyDialog::Accepted)
    {
        server = new QTcpServer();
        server->listen(QHostAddress::Any, 8888);
        QObject::connect(server, &QTcpServer::newConnection, this, &MainWindow::server_new_connection);
    }
}//创建服务器

void MainWindow::create_dialog2()
{
    QInputDialog *enter_IP = new QInputDialog(this);
    enter_IP->setGeometry(400, 350, 400, 300);
    QFont font;
    font.setPointSize(20);
    enter_IP->setFont(font);
    bool ok = false;
    QString enterIP = enter_IP->getText(this, "连接服务器", "Enter IP:", QLineEdit::Normal, "请输入IP地址", &ok);

    if(ok && !enterIP.isEmpty())
    {
        if(!check_IP(enterIP))
        {
            QMessageBox::information(NULL, "提示", "IP地址格式错误，请重新输入!", QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        clientsocket = new QTcpSocket();
        clientsocket->connectToHost(QHostAddress(enterIP), 8888);
        QObject::connect(clientsocket, &QTcpSocket::readyRead, this, &MainWindow::update_client);
        QObject::connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::Disconnect);
        ui->centralwidget->has_connected = true;
    }
}//客户端连接服务器

bool MainWindow::check_IP(QString enterIP)
{
    char tmp[100];
    std::string cpy = enterIP.toStdString();
    memcpy(tmp, cpy.c_str(), cpy.size());
    int a, b, c, d;
    if(sscanf(tmp, "%d.%d.%d.%d", &a, &b, &c, &d) == 4)
    {
        if(a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255)
            return true;
    }
    return false;
}//检查输入IP格式

void MainWindow::server_new_connection()
{
    serversocket = server->nextPendingConnection();
    if(!serversocket)
    {
        QMessageBox::information(this, "错误", "获取客户端连接失败", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    QMessageBox::information(this, "提示", "恭喜，获取客户端连接成功", QMessageBox::Ok, QMessageBox::Ok);
    QObject::connect(serversocket, &QTcpSocket::readyRead, this, &MainWindow::update_server);
    QObject::connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::Disconnect);
    ui->centralwidget->has_connected = true;
}//服务器接收连接

void MainWindow::update_server()
{
    QDataStream in(serversocket);
    if(server_blocksize == 0)
    {
        if(serversocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> server_blocksize;
    }
    if(serversocket->bytesAvailable() < server_blocksize)
        return;
    int x, y, a;
    in >> x >> y >> a;
    //数据读取
    if(x + y > 0)
    {
        if(a != -1)
            ui->centralwidget->click_chesspiece(x, y, false, a);
        else
            ui->centralwidget->click_chesspiece(x, y, false);
    }//鼠标点击操作
    else if(x + y == 0)
    {
        if(!is_ready)
        {
            QMessageBox::information(NULL, "提示", "客户端已准备开始！", QMessageBox::Ok, QMessageBox::Ok);
            is_ready = true;
            QObject::connect(ui->actionStart, &QAction::triggered, this, [&](){
                emit game_start();
            });
        }
        else
            emit game_start();
    }//游戏开始操作
    else if(x + y == -2)
    {
        ui->centralwidget->has_give_up = true;
        ui->centralwidget->give_up();
    }//认输操作
    else if(x + y == -4)
    {
        QMessageBox::information(NULL, "提示", "客户端已与您断开连接！", QMessageBox::Ok, QMessageBox::Ok);
        ui->centralwidget->has_connected = false;
        serversocket->close();
    }//断开连接操作
    server_blocksize = 0;
}//更新服务器数据

void MainWindow::update_client()
{
    QDataStream in(clientsocket);
    if(client_blocksize == 0)
    {
        if(clientsocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> client_blocksize;
    }
    if(clientsocket->bytesAvailable() < client_blocksize)
        return;
    int x, y, a;
    in >> x >> y >> a;
    //读取数据
    if(x + y > 0)
    {
        if(a != -1)
            ui->centralwidget->click_chesspiece(x, y, false, a);
        else
            ui->centralwidget->click_chesspiece(x, y, false);
    }//鼠标点击操作
    else if(x + y == 0)
    {
        if(!is_ready)
            QMessageBox::information(NULL, "提示", "服务器端已准备开始！", QMessageBox::Ok, QMessageBox::Ok);
        else
        {
            emit game_start();
            ui->centralwidget->set_first_turn(a);
            ui->centralwidget->change_side();
        }
    }//游戏开始操作
    else if(x + y == -2)
    {
        ui->centralwidget->has_give_up = true;
        ui->centralwidget->give_up();
    }//认输操作
    else if(x + y == -4)
    {
        QMessageBox::information(NULL, "提示", "服务器已关闭", QMessageBox::Ok, QMessageBox::Ok);
        ui->centralwidget->has_connected = false;
    }//断开连接操作
    client_blocksize = 0;
}//更新客户端数据

void MainWindow::ready_to_write(int x, int y, int a)
{
    if(serversocket)
        serverwrite(x, y, a);
    if(clientsocket)
        clientwrite(x, y, a);
}//准备写入数据

void MainWindow::serverwrite(int x, int y, int a)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << x << y << a;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    serversocket->write(block);
    serversocket->flush();
}//服务端写入数据

void MainWindow::clientwrite(int x, int y, int a)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << x << y << a;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    clientsocket->write(block);
    clientsocket->flush();
}//客户端写入数据

void MainWindow::Disconnect()
{
    if(serversocket)
    {
        ready_to_write(-2, -2);
        ui->centralwidget->has_connected = false;
        serversocket->close();
        QMessageBox::information(NULL, "提示", "服务器已关闭!", QMessageBox::Ok, QMessageBox::Ok);
    }
    if(clientsocket)
    {
        ready_to_write(-2, -2);
        ui->centralwidget->has_connected = false;
        clientsocket->disconnectFromHost();
        QMessageBox::information(NULL, "提示", "已断开与服务器的连接!", QMessageBox::Ok, QMessageBox::Ok);
    }
}//断开连接
