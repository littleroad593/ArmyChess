#include "Chesspiece.h"

std::vector<QString> Chesspiece::paths = create_paths();
std::vector<QString> path_referrence = Chesspiece::paths;

Chesspiece::Chesspiece(QWidget *parent) : QLabel(parent)
{

}

Chesspiece::~Chesspiece()
{

}

std::vector<QString> Chesspiece::create_paths()
{
    std::vector<QString> tmpv;

    tmpv.push_back(":/new/prefix1/png/junqi_hong.png");
    tmpv.push_back(":/new/prefix1/png/dilei_hong.png");
    tmpv.push_back(":/new/prefix1/png/dilei_hong.png");
    tmpv.push_back(":/new/prefix1/png/dilei_hong.png");
    tmpv.push_back(":/new/prefix1/png/siling_hong.png");
    tmpv.push_back(":/new/prefix1/png/junzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/shizhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/shizhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/lvzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/lvzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/tuanzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/tuanzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/yingzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/yingzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/lianzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/lianzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/lianzhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/paizhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/paizhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/paizhang_hong.png");
    tmpv.push_back(":/new/prefix1/png/gongbing_hong.png");
    tmpv.push_back(":/new/prefix1/png/gongbing_hong.png");
    tmpv.push_back(":/new/prefix1/png/gongbing_hong.png");
    tmpv.push_back(":/new/prefix1/png/zhadan_hong.png");
    tmpv.push_back(":/new/prefix1/png/zhadan_hong.png");

    tmpv.push_back(":/new/prefix1/png/junqi_lan.png");
    tmpv.push_back(":/new/prefix1/png/dilei_lan.png");
    tmpv.push_back(":/new/prefix1/png/dilei_lan.png");
    tmpv.push_back(":/new/prefix1/png/dilei_lan.png");
    tmpv.push_back(":/new/prefix1/png/siling_lan.png");
    tmpv.push_back(":/new/prefix1/png/junzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/shizhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/shizhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/lvzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/lvzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/tuanzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/tuanzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/yingzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/yingzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/lianzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/lianzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/lianzhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/paizhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/paizhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/paizhang_lan.png");
    tmpv.push_back(":/new/prefix1/png/gongbing_lan.png");
    tmpv.push_back(":/new/prefix1/png/gongbing_lan.png");
    tmpv.push_back(":/new/prefix1/png/gongbing_lan.png");
    tmpv.push_back(":/new/prefix1/png/zhadan_lan.png");
    tmpv.push_back(":/new/prefix1/png/zhadan_lan.png");

    return tmpv;
}//创建图片地址vector

int Chesspiece::turnover(int a)
{
    QString path;
    if(a == -1)
    {
        srand((unsigned)time(NULL));
        a = rand() % paths.size();
    }
    path = paths[a];
    paths.erase(paths.begin() + a);

    for(int i = 0; i < (int)path_referrence.size(); i++)
    {
        if(path_referrence[i] == path)
        {
            if(i < 25) {Is_red = true;}
            else {Is_red = false;}
            i %= 25;
            if(i == 0) {chess_ID = 0;}//军旗
            if(i >= 1 && i <= 3) {chess_ID = 1;}//地雷
            if(i == 4) {chess_ID = 2;}//司令
            if(i == 5) {chess_ID = 3;}//军长
            if(i == 6 || i == 7) {chess_ID = 4;}//师长
            if(i == 8 || i == 9) {chess_ID = 5;}//旅长
            if(i == 10 || i == 11) {chess_ID = 6;}//团长
            if(i == 12 || i == 13) {chess_ID = 7;}//营长
            if(i >= 14 && i <= 16) {chess_ID = 8;}//连长
            if(i >= 17 && i <= 19) {chess_ID = 9;}//排长
            if(i >= 20 && i <= 22) {chess_ID = 10;}//工兵
            if(i == 23 || i == 24) {chess_ID = 11;}//炸弹
            Is_dead = false;
            Is_open = true;
            break;
        }
    }

    QPixmap *pixmap = new QPixmap(path);
    pixmap->scaled(size(), Qt::KeepAspectRatio);
    setScaledContents(true);
    setPixmap(*pixmap);

    return a;
}//随机翻棋

int Chesspiece::getChessID()
{
    return chess_ID;
}

bool Chesspiece::is_red()
{
    return Is_red;
}

