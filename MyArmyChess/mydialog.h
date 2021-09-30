#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QNetworkInterface>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
    void create_server_window();

private:
    Ui::MyDialog *ui;

public slots:
    //void create_the_connection();
};

#endif // MYDIALOG_H
