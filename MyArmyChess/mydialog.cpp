#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::create_server_window()
{
    QLabel *host_IP = new QLabel(this);
    host_IP->setGeometry(80, 120, 300, 30);
    QFont font;
    font.setPointSize(20);
    host_IP->setFont(font);
    QString hostIP;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress::LocalHost)
            hostIP = address.toString();
    }
    host_IP->setText("Host IP: " + hostIP);
}//设置服务器对话框


