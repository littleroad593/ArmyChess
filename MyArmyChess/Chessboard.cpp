#include "Chessboard.h"

Chessboard::Chessboard(QWidget *parent) : QWidget(parent), v(new QVector<railway_pos>[32])
{

}

Chessboard::~Chessboard()
{
    delete[] v;
}

void Chessboard::setRailway()
{
    v[0].push_back({chess_x[0], chess_y[1], 0, 0});
    v[0].push_back({chess_x[0], chess_y[2], 1, 0});
    v[0].push_back({chess_x[1], chess_y[1], 20, 0});
    for(int i = 1; i < 9; i++)
    {
        v[i].push_back({chess_x[0], chess_y[i + 1], i, 0});
        v[i].push_back({chess_x[0], chess_y[i], i - 1, 0});
        v[i].push_back({chess_x[0], chess_y[i + 2], i + 1, 0});
    }
    v[9].push_back({chess_x[0], chess_y[10], 9, 0});
    v[9].push_back({chess_x[0], chess_y[9], 8, 0});
    v[9].push_back({chess_x[1], chess_y[10], 29, 0});
    v[4].push_back({chess_x[1], chess_y[5], 23, 0});
    v[5].push_back({chess_x[1], chess_y[6], 26, 0});

    v[10].push_back({chess_x[4], chess_y[1], 10, 0});
    v[10].push_back({chess_x[4], chess_y[2], 11, 0});
    v[10].push_back({chess_x[3], chess_y[1], 22, 0});
    for(int i = 1; i < 9; i++)
    {
        v[i + 10].push_back({chess_x[4], chess_y[i + 1], i + 10, 0});
        v[i + 10].push_back({chess_x[4], chess_y[i], i + 9, 0});
        v[i + 10].push_back({chess_x[4], chess_y[i + 2], i + 11, 0});
    }
    v[19].push_back({chess_x[4], chess_y[10], 19, 0});
    v[19].push_back({chess_x[4], chess_y[9], 18, 0});
    v[19].push_back({chess_x[3], chess_y[10], 31, 0});
    v[14].push_back({chess_x[3], chess_y[5], 25, 0});
    v[15].push_back({chess_x[3], chess_y[6], 28, 0});

    v[20].push_back({chess_x[1], chess_y[1], 20, 0});
    v[20].push_back({chess_x[0], chess_y[1], 0, 0});
    v[20].push_back({chess_x[2], chess_y[1], 21, 0});
    v[21].push_back({chess_x[2], chess_y[1], 21, 0});
    v[21].push_back({chess_x[1], chess_y[1], 20, 0});
    v[21].push_back({chess_x[3], chess_y[1], 22, 0});
    v[22].push_back({chess_x[3], chess_y[1], 22, 0});
    v[22].push_back({chess_x[2], chess_y[1], 21, 0});
    v[22].push_back({chess_x[4], chess_y[1], 10, 0});

    v[23].push_back({chess_x[1], chess_y[5], 23, 0});
    v[23].push_back({chess_x[0], chess_y[5], 4, 0});
    v[23].push_back({chess_x[2], chess_y[5], 24, 0});
    v[24].push_back({chess_x[2], chess_y[5], 24, 0});
    v[24].push_back({chess_x[1], chess_y[5], 23, 0});
    v[24].push_back({chess_x[3], chess_y[5], 25, 0});
    v[24].push_back({chess_x[2], chess_y[6], 27, 0});
    v[25].push_back({chess_x[3], chess_y[5], 25, 0});
    v[25].push_back({chess_x[2], chess_y[5], 24, 0});
    v[25].push_back({chess_x[4], chess_y[5], 14, 0});

    v[26].push_back({chess_x[1], chess_y[6], 26, 0});
    v[26].push_back({chess_x[0], chess_y[6], 5, 0});
    v[26].push_back({chess_x[2], chess_y[6], 27, 0});
    v[27].push_back({chess_x[2], chess_y[6], 27, 0});
    v[27].push_back({chess_x[1], chess_y[6], 26, 0});
    v[27].push_back({chess_x[3], chess_y[6], 28, 0});
    v[27].push_back({chess_x[2], chess_y[5], 24, 0});
    v[28].push_back({chess_x[3], chess_y[6], 28, 0});
    v[28].push_back({chess_x[2], chess_y[6], 27, 0});
    v[28].push_back({chess_x[4], chess_y[6], 15, 0});

    v[29].push_back({chess_x[1], chess_y[10], 29, 0});
    v[29].push_back({chess_x[0], chess_y[10], 9, 0});
    v[29].push_back({chess_x[2], chess_y[10], 30, 0});
    v[30].push_back({chess_x[2], chess_y[10], 30, 0});
    v[30].push_back({chess_x[1], chess_y[10], 29, 0});
    v[30].push_back({chess_x[3], chess_y[10], 31, 0});
    v[31].push_back({chess_x[3], chess_y[10], 31, 0});
    v[31].push_back({chess_x[2], chess_y[10], 30, 0});
    v[31].push_back({chess_x[4], chess_y[10], 19, 0});
}//设置铁路线

void Chessboard::mousePressEvent(QMouseEvent *e)
{
    if(is_end)
        return;
    if(!my_turn && has_connected)
        return;
    if (e->button() != Qt::LeftButton)
        return;
    if(!start && select_a_chesspiece(e->pos().x(), e->pos().y()) != -1)
        return;
    click_chesspiece(e->pos().x(), e->pos().y());
}//鼠标左键单击事件

void Chessboard::click_chesspiece(int x, int y, bool signal, int a)
{
    static int click_time = 0;
    switch(click_time)
    {
        case(0):
        {
            c1 = select_a_chesspiece(x, y);
            if(c1 != -1)
            {
                if (chesspieces[c1]->pixmap().cacheKey() == QPixmap(":/new/prefix1/png/weizhi.png").cacheKey())
                {
                    if(a != -1)
                        chesspieces[c1]->turnover(a);
                    else
                    {
                        a = chesspieces[c1]->turnover();
                        if(signal && has_connected)
                            emit has_clicked(x, y, a);
                    }
                    update_round(c1);
                    return;
                }//未翻开则翻开
                if(has_decided_color && my_turn && my_color[0] != chesspieces[c1]->is_red())
                    return;
                if(has_decided_color && opponent_turn && opponent_color[0] != chesspieces[c1]->is_red())
                    return;
                if(signal && has_connected)
                    emit has_clicked(x, y, a);
                click_time++;
            }
        }break;//一次点击

        case(1):
        {
            if(!has_decided_color)
            {
                if(signal && has_connected)
                    emit has_clicked(x, y);
                click_time = 0;
                return;
            }//未确定颜色不能移动棋子
            c2 = select_a_chesspiece(x, y);
            if(c2 == -1)//终点无棋子
            {
                if(signal && has_connected)
                    emit has_clicked(x, y);
                int new_x = -1, new_y = -1;
                for(int i = 0; i < 5; i++)
                {
                    if(x >= chess_x[i] && x <= chess_x[i] + chess_length)
                        new_x = chess_x[i];
                }
                for(int i = 0; i < 12; i++)
                {
                    if(y >= chess_y[i] && y <= chess_y[i] + chess_height)
                        new_y = chess_y[i];
                }//确定位置坐标
                if(new_x != -1 && new_y != -1)
                {
                    if(cangoto(c1, new_x, new_y) && !chess_in_the_way(c1, new_x, new_y))
                    {
                        chesspieces[c1]->move(new_x, new_y);
                        update_round();
                    }
                }
                click_time = 0;
                return;
            }

            if(c2 != -1)//终点有棋子
            {
                if (chesspieces[c2]->pixmap().cacheKey() == QPixmap(":/new/prefix1/png/weizhi.png").cacheKey())
                {
                    if(a != -1)
                        chesspieces[c2]->turnover(a);
                    else
                    {
                        a = chesspieces[c2]->turnover();
                        if(signal && has_connected)
                            emit has_clicked(x, y, a);
                    }
                    click_time = 0;
                    update_round(c2);
                    return;
                }//未翻开则翻开
                if(chesspieces[c1]->is_red() == chesspieces[c2]->is_red())
                {
                    if(signal && has_connected)
                        emit has_clicked(x, y);
                    c2 = -1;
                    click_time = 0;
                    return;
                }//同色返回
                if(cangoto(c1, chesspieces[c2]->pos().x(), chesspieces[c2]->pos().y()) && !chess_in_the_field(c2) &&\
                           !chess_in_the_way(c1, chesspieces[c2]->pos().x(), chesspieces[c2]->pos().y()))
                {
                    if(signal && has_connected)
                        emit has_clicked(x, y);
                    compare_chess();
                    c2 = -1;
                    click_time = 0;
                    return;
                }
                if(signal && has_connected)
                    emit has_clicked(x, y);
                c2 = -1;
                click_time = 0;
            }

        }break;//二次点击
    }
}//点击棋子

int Chessboard::select_a_chesspiece(int x, int y)
{
    for(int i = 0; i < chesspieces.size(); i++)
    {
        if(chesspieces[i]->Is_dead)
            continue;
        QPoint chessq = chesspieces[i]->pos();
        if (x >= chessq.x() && x <= chessq.x() + chess_length && y >= chessq.y() && y <= chessq.y() + chess_height)
            return i;
    }
    return -1;
}//选中棋子

bool Chessboard::cangoto(int c1, int x, int y)
{
    int ID = chesspieces[c1]->getChessID();
    if(ID <= 1)
        return false;
    QPoint p = chesspieces[c1]->pos();

    if(p.y() == chess_y[0] && p.x() >= chess_x[1] && p.x() <= chess_x[3])
    {
        if((p.x() == x && y == chess_y[1]) || (p.y() == y && abs(p.x() - x) == chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//公路线上行

    if(p.y() == chess_y[11] && p.x() >= chess_x[1] && p.x() <= chess_x[3])
    {
        if((p.x() == x && y == chess_y[10]) || (p.y() == y && abs(p.x() - x) == chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//公路线下行

    if((p.x() == chess_x[0] && p.y() == chess_y[0]))
    {
        if((p.x() == x && y == chess_y[1]) || (p.y() == y && x == chess_x[1]))
            return true;
        return false;
    }//棋盘左上角

    if((p.x() == chess_x[0] && p.y() == chess_y[11]))
    {
        if((p.x() == x && y == chess_y[10]) || (p.y() == y && x == chess_x[1]))
            return true;
        return false;
    }//棋盘左下角

    if((p.x() == chess_x[4] && p.y() == chess_y[0]))
    {
        if((p.x() == x && y == chess_y[1]) || (p.y() == y && x == chess_x[3]))
            return true;
        return false;
    }//棋盘右上角

    if((p.x() == chess_x[4] && p.y() == chess_y[11]))
    {
        if((p.x() == x && y == chess_y[10]) || (p.y() == y && x == chess_x[3]))
            return true;
        return false;
    }//棋盘右下角

    if((p.x() == chess_x[1] && (p.y() == chess_y[3] || p.y() == chess_y[8]))\
             || (p.x() == chess_x[2] && (p.y() == chess_y[2] || p.y() == chess_y[4] || p.y() == chess_y[7] || p.y() == chess_y[9]))\
             || (p.x() == chess_x[3] && (p.y() == chess_y[3] || p.y() == chess_y[8])))
    {
        if((abs(x - p.x()) == chess_x[1] - chess_x[0] && y == p.y()) || (x == p.x() && abs(y - p.y()) == chess_y[1] - chess_y[0]))
            return true;
        return false;
    }//公路线中央八子

    if((p.x() == chess_x[1] && (p.y() == chess_y[2] || p.y() == chess_y[4] || p.y() == chess_y[7] || p.y() == chess_y[9] ))\
             || (p.x() == chess_x[2] && (p.y() == chess_y[3] || p.y() == chess_y[8]))\
             || (p.x() == chess_x[3] && (p.y() == chess_y[2] || p.y() == chess_y[4] || p.y() == chess_y[7] || p.y() == chess_y[9] )))
    {
        if(abs(x - p.x()) <= chess_x[1] - chess_x[0] && abs(y - p.y()) <= chess_y[1] - chess_y[0])
            return true;
        return false;
    }//行营

    if(ID == 10)
        if(((x == chess_x[0] || x == chess_x[4]) && y >= chess_y[1] && y <= chess_y[10]) || y == chess_y[1] ||\
                y == chess_y[5] || y == chess_y[6] || y == chess_y[10])
            return true;//工兵线路

    if((p.x() == chess_x[0] && p.y() == chess_y[1]) || (p.x() == chess_x[0] && p.y() == chess_y[6]))
    {
        if(p.x() == x || p.y() == y || (y - p.y() == chess_y[1] - chess_y[0] && x - p.x() == chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线双左上角

    if((p.x() == chess_x[0] && p.y() == chess_y[5]) || (p.x() == chess_x[0] && p.y() == chess_y[10]))
    {
        if(p.x() == x || p.y() == y || (p.y() - y == chess_y[1] - chess_y[0] && x - p.x() == chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线双左下角

    if((p.x() == chess_x[4] && p.y() == chess_y[1]) || (p.x() == chess_x[4] && p.y() == chess_y[6]))
    {
        if(p.x() == x || p.y() == y || (y - p.y() == chess_y[1] - chess_y[0] && p.x() - x == chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线双右上角

    if((p.x() == chess_x[4] && p.y() == chess_y[5]) || (p.x() == chess_x[4] && p.y() == chess_y[10]))
    {
        if(p.x() == x || p.y() == y || (p.y() - y == chess_y[1] - chess_y[0] && p.x() - x == chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线双右下角

    if((p.x() == chess_x[0] && p.y() == chess_y[2]) || (p.x() == chess_x[0] && p.y() == chess_y[4])\
            || (p.x() == chess_x[0] && p.y() == chess_y[7]) || (p.x() == chess_x[0] && p.y() == chess_y[9]))
    {
        if(p.x() == x || (p.y() == y && x == chess_x[1]))
            return true;
        return false;
    }//铁路线左列（除中间）

    if((p.x() == chess_x[4] && p.y() == chess_y[2]) || (p.x() == chess_x[4] && p.y() == chess_y[4])\
            || (p.x() == chess_x[4] && p.y() == chess_y[7]) || (p.x() == chess_x[4] && p.y() == chess_y[9]))
    {
        if(p.x() == x || (p.y() == y && x == chess_x[3]))
            return true;
        return false;
    }//铁路线右列（除中间）

    if((p.x() == chess_x[1] && p.y() == chess_y[1]) || (p.x() == chess_x[3] && p.y() == chess_y[1])\
            || (p.x() == chess_x[1] && p.y() == chess_y[10]) || (p.x() == chess_x[3] && p.y() == chess_y[10]))
    {
        if(p.y() == y || (p.x() == x && abs(y - p.y()) == chess_y[1] - chess_y[0]))
            return true;
        return false;
    }//铁路线上下行（除中间）

    if((p.x() == chess_x[1] && p.y() == chess_y[5]) ||(p.x() == chess_x[3] && p.y() == chess_y[5]))
    {
        if(p.y() == y || (p.x() == x && y == chess_y[4]))
            return true;
        return false;
    }//铁路线中上行（除中间）

    if((p.x() == chess_x[1] && p.y() == chess_y[6]) ||(p.x() == chess_x[3] && p.y() == chess_y[6]))
    {
        if(p.y() == y || (p.x() == x && y == chess_y[7]))
            return true;
        return false;
    }//铁路线中下行（除中间）

    if((p.x() == chess_x[0] && p.y() == chess_y[3]) || (p.x() == chess_x[0] && p.y() == chess_y[8]))
    {
        if(p.x() == x || (x == chess_x[1] && abs(y - p.y()) <= chess_y[1] - chess_y[0]))
            return true;
        return false;
    }//铁路线左列中间

    if((p.x() == chess_x[4] && p.y() == chess_y[3]) || (p.x() == chess_x[4] && p.y() == chess_y[8]))
    {
        if(p.x() == x || (x == chess_x[3] && abs(y - p.y()) <= chess_y[1] - chess_y[0]))
            return true;
        return false;
    }//铁路线右列中间

    if(p.x() == chess_x[2] && p.y() == chess_y[1])
    {
        if(p.y() == y || (x == chess_x[2] && y == chess_y[0]) ||\
                (y - p.y() == chess_y[1] - chess_y[0] && abs(x - p.x()) <= chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线上行中间

    if((p.x() == chess_x[2] && p.y() == chess_y[5]))
    {
        if(p.y() == y || (x == chess_x[2] && y == chess_y[6]) ||\
                (p.y() - y == chess_y[1] - chess_y[0] && abs(x - p.x()) <= chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线中上行中间

    if(p.x() == chess_x[2] && p.y() == chess_y[6])
    {
        if(p.y() == y || (x == chess_x[2] && y == chess_y[5]) ||\
                (y - p.y() == chess_y[1] - chess_y[0] && abs(x - p.x()) <= chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线中下行中间

    if(p.x() == chess_x[2] && p.y() == chess_y[10])
    {
        if(p.y() == y || (x == chess_x[2] && y == chess_y[11]) ||\
                (p.y() - y == chess_y[1] - chess_y[0] && abs(x - p.x()) <= chess_x[1] - chess_x[0]))
            return true;
        return false;
    }//铁路线下行中间

    return false;
}//棋子能否到达此处

bool Chessboard::chess_in_the_way(int c1, int x, int y)
{
    int ID = chesspieces[c1]->getChessID();
    QPoint p = chesspieces[c1]->pos();
    if(ID != 10)
    {
        if(x == p.x())
        {
            for(int i = 0; i < chesspieces.size(); i++)
            {
                if(chesspieces[i]->Is_dead)
                    continue;
                if(chesspieces[i]->pos().y() > qMin(y, p.y()) && chesspieces[i]->pos().y() < qMax(y, p.y())\
                        && chesspieces[i]->pos().x() == p.x())
                    return true;
            }
        }
        if(y == p.y())
        {
            for(int i = 0; i < chesspieces.size(); i++)
            {
                if(chesspieces[i]->Is_dead)
                    continue;
                if(chesspieces[i]->pos().x() > qMin(x, p.x()) && chesspieces[i]->pos().x() < qMax(x, p.x())\
                        && chesspieces[i]->pos().y() == p.y())
                    return true;
            }
        }
    }//非工兵情况
    else
    {
        int n1 = -1, n2 = -1;
        for(int i = 0; i < 32; i++)
        {
            if(v[i][0].x == p.x() && v[i][0].y == p.y())
                n1 = i;//确定初始位置
            if(v[i][0].x == x && v[i][0].y == y)
                n2 = i;//判断终点是否在铁路线上
            if(n1 != -1 && n2 != -1)
                break;
        }
        if(n1 == -1 || n2 == -1)
            return false;
        for(int i = 0; i < 32; i++)
            v[i][0].has_checked = false;
        search_way_for_gongbing(n1, x, y);
        if(flag)
        {
            flag = false;
            return false;
        }
        return true;
    }//工兵情况
    return false;
}//是否有棋子挡路

void Chessboard::search_way_for_gongbing(int n1, int x, int y)
{
    if(v[n1][0].x == x && v[n1][0].y == y)
    {
        flag = true;
        return;
    }//到达终点返回
    int new_n1;
    for(auto it = v[n1].begin() + 1; it != v[n1].end(); it++)
    {
        bool flag1 = true;
        if(v[it->num][0].has_checked)
            continue;
        for(int i = 0; i < chesspieces.size(); i++)
        {
            if(chesspieces[i]->Is_dead)
                continue;
            if(chesspieces[i]->pos().x() == it->x && chesspieces[i]->pos().y() == it->y)
            {
                if(!(it->x == x && it->y == y &&\
                     (chesspieces[i]->getChessID() <= 1 || chesspieces[i]->getChessID() >= 10)))
                {
                    flag1 = false;
                    break;
                }
            }
        }
        v[it->num][0].has_checked = true;
        if(flag1)
        {
            new_n1 = it->num;
            search_way_for_gongbing(new_n1, x, y);
            if(flag)
                break;
        }
    }
}//工兵寻路

bool Chessboard::chess_in_the_field(int ID)
{
    QPoint p = chesspieces[ID]->pos();
    if((p.x() == chess_x[1] && (p.y() == chess_y[2] || p.y() == chess_y[4] || p.y() == chess_y[7] || p.y() == chess_y[9] ))\
             || (p.x() == chess_x[2] && (p.y() == chess_y[3] || p.y() == chess_y[8]))\
             || (p.x() == chess_x[3] && (p.y() == chess_y[2] || p.y() == chess_y[4] || p.y() == chess_y[7] || p.y() == chess_y[9])))
        return true;
    return false;
}//棋子是否在行营中

void Chessboard::compare_chess()
{
    int ID1 = chesspieces[c1]->getChessID(), ID2 = chesspieces[c2]->getChessID();

    if((ID1 == 11 && ID2 != 0) || ID2 == 11 || ID1 == ID2)
    {
        chesspieces[c1]->Is_dead = true;
        chesspieces[c1]->clear();
        chesspieces[c2]->Is_dead = true;
        chesspieces[c2]->clear();
        if(chesspieces[c1]->is_red())
        {
            red_counter[ID1]--;
            blue_counter[ID2]--;
        }
        else
        {
            blue_counter[ID1]--;
            red_counter[ID2]--;
        }
        update_round();
        return;
    }//同归于尽

    if(ID1 < ID2 || (ID1 == 10 && ID2 == 1))
    {
        chesspieces[c2]->Is_dead = true;
        chesspieces[c2]->clear();
        chesspieces[c1]->move(chesspieces[c2]->pos().x(), chesspieces[c2]->pos().y());
        if(chesspieces[c1]->is_red())
            blue_counter[ID2]--;
        else
            red_counter[ID2]--;
        update_round();
        return;
    }//吃子

    if(ID2 == 0 && chesspieces[c1]->is_red() && blue_no_mine())
    {
        chesspieces[c2]->Is_dead = true;
        chesspieces[c2]->clear();
        if(ID1 == 11)
        {
            chesspieces[c1]->Is_dead = true;
            chesspieces[c1]->clear();
        }
        else
            chesspieces[c1]->move(chesspieces[c2]->pos().x(), chesspieces[c2]->pos().y());
        if(my_turn)
            I_win = true;
        else
            Opponent_win = true;
        is_end = true;
        update_round();
        return;
    }//红方获胜

    if(ID2 == 0 && !chesspieces[c1]->is_red() && red_no_mine())
    {
        chesspieces[c2]->Is_dead = true;
        chesspieces[c2]->clear();
        if(ID1 == 11)
        {
            chesspieces[c1]->Is_dead = true;
            chesspieces[c1]->clear();
        }
        chesspieces[c1]->move(chesspieces[c2]->pos().x(), chesspieces[c2]->pos().y());
        if(my_turn)
            I_win = true;
        else
            Opponent_win = true;
        is_end = true;
        update_round();
        return;
    }//蓝方获胜
}//棋子比较

bool Chessboard::red_no_mine()
{
    if(red_counter[1] == 0)
        return true;
    return false;
}//红方地雷检测

bool Chessboard::blue_no_mine()
{
    if(blue_counter[1] == 0)
        return true;
    return false;
}//蓝方地雷检测

void Chessboard::update_round(int ID)
{
    if(!has_decided_color && ID != -1)
        decide_color(ID);
    if(!giveup)
    {
       round_counter->setText("Round: " + QString::number(++round));
       bool tmp = my_turn;
       my_turn = opponent_turn;
       opponent_turn = tmp;
       if(my_turn)
       {
           if(has_decided_color)
               if(all_cannot_move(my_color[0]))
               {
                    is_end = true;
                    Opponent_win = true;
               }
           turn_display->setText("我的回合");
       }
       else
       {
           if(has_decided_color)
               if(all_cannot_move(opponent_color[0]))
               {
                   is_end = true;
                   I_win = true;
               }
           turn_display->setText("对方回合");
       }
    }//轮次转换
    second = 0;
    timer->stop();
    time_left->setText("步时剩余: 20秒");
    timer->start(1000);
    if(round >= 20)
    {
        give_up_button->setVisible(true);//超过20轮可认输
        give_up_button->setEnabled(true);
    }
    if(is_end)
    {
        timer->stop();
        give_up_button->setEnabled(false);
        check_who_wins();
    }//如果结束则判断胜负
}//更新轮数信息

bool Chessboard::all_cannot_move(bool color)
{
    for(int i = 0; i < chesspieces.size(); i++)
        if(!chesspieces[i]->Is_open)
            return false;
    for(int i = 0; i < chesspieces.size(); i++)
    {
        if(chesspieces[i]->is_red() != color || chesspieces[i]->Is_dead)
            continue;
        if(!chess_in_the_next_pos(i))
            return false;
    }
    return true;
}//非静止棋子是否全部死亡

bool Chessboard::chess_in_the_next_pos(int ID)
{
    bool flag = false;
    int x = chesspieces[ID]->pos().x(), y = chesspieces[ID]->pos().y();
    int xs[3] = {x - chess_x[1] + chess_x[0], x, x + chess_x[1] - chess_x[0]};
    int ys[3];
    if(y != chess_y[5] && y != chess_y[6])
    {
        ys[0] = y - chess_y[1] + chess_y[0];
        ys[1] = y;
        ys[2] = y + chess_y[1] - chess_y[0];
    }
    else if(y == chess_y[5])
    {
        ys[0] = y - chess_y[1] + chess_y[0];
        ys[1] = y;
        ys[2] = y + chess_y[6] - chess_y[5];
    }
    else if(y == chess_y[6])
    {
        ys[0] = y - chess_y[6] + chess_y[5];
        ys[1] = y;
        ys[2] = y + chess_y[1] - chess_y[0];
    }
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(xs[i] < chess_x[0] || xs[i] > chess_x[4] || ys[j] < chess_y[0] || ys[j] > chess_y[11])
                continue;//出界
            if(!cangoto(ID, xs[i], ys[j]) && chesspieces[ID]->getChessID() != 10)
                continue;//到不了
            if(chesspieces[ID]->getChessID() == 10)
            {
                if(!cangoto(ID, xs[i], ys[j]))
                    continue;
                else if(on_railway(xs[i], ys[j]) && xs[i] != x && ys[j] != y)
                    continue;
            }
            for(int k = 0; k < chesspieces.size(); k++)
                if(chesspieces[k]->pos().x() == xs[i] && chesspieces[k]->pos().y() == ys[j] && !chesspieces[k]->Is_dead)
                {
                    if(chesspieces[ID]->is_red() != chesspieces[k]->is_red() &&\
                            (chesspieces[ID]->getChessID() <= chesspieces[k]->getChessID() ||\
                             (chesspieces[ID]->getChessID() == 11 && chesspieces[ID]->getChessID() != 0)) &&\
                            !chess_in_the_field(k))//颜色不同、序号小或是炸弹、邻位棋子不在营中
                        return false;
                    flag = true;
                    break;
                }
            if(!flag)
                return false;
            flag = false;
        }
    return true;
}//邻位是否有棋子

bool Chessboard::on_railway(int x, int y)
{
    for(int i = 0; i < 32; i++)
        if(v[i][0].x == x && v[i][0].y == y)
            return true;
    return false;
}//坐标是否在铁轨上

int Chessboard::set_first_turn(int a)
{
    srand((unsigned)time(NULL));
    if(a == -1)
        a = rand() % 2;
    if(a)
    {
        my_turn = true;
        opponent_turn = false;
        turn_display->setText("我的回合");
    }
    else
    {
        my_turn = false;
        opponent_turn = true;
        turn_display->setText("对方回合");
    }
    turn_display->setVisible(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_time_counter()));
    timer->start(1000);
    return a;
}//随机猜先

void Chessboard::decide_color(int ID)
{
    if(my_turn)
    {
        my_color.push_back(chesspieces[ID]->is_red());
        if(my_color.size() == 2)
        {
            if(my_color[0] == my_color[1])
            {
                has_decided_color = true;
                my_color.pop_back();
                opponent_color.clear();
                opponent_color.push_back(!my_color[0]);
                if(my_color[0])
                    color_display->setText("我的颜色: 红色");
                else
                    color_display->setText("我的颜色: 蓝色");
            }
            else
            {
                my_color[0] = my_color[1];
                my_color.pop_back();
            }
        }
    }
    else
    {
        opponent_color.push_back(chesspieces[ID]->is_red());
        if(opponent_color.size() == 2)
        {
            if(opponent_color[0] == opponent_color[1])
            {
                has_decided_color = true;
                opponent_color.pop_back();
                my_color.clear();
                my_color.push_back(!opponent_color[0]);
                if(my_color[0])
                    color_display->setText("我的颜色: 红色");
                else
                    color_display->setText("我的颜色: 蓝色");
            }
            else
            {
                opponent_color[0] = opponent_color[1];
                opponent_color.pop_back();
            }
        }
    }
}//确定双方所持颜色

void Chessboard::update_time_counter()
{
    second++;
    if(second > 20)
    {
        if(my_turn)
        {
            overtime_lose(++my_overtime);
            Myovertime->setText("我方超时: " + QString::number(my_overtime) + "次");
        }
        else
        {
            overtime_lose(++opponent_overtime);
            Opponentovertime->setText("对方超时: " + QString::number(opponent_overtime) + "次");
        }
        update_round();
    }
    else
        time_left->setText("步时剩余: " + QString::number(20 - second) + "秒");
}//更新计时器

void Chessboard::overtime_lose(int overtime)
{
    if(overtime < 3)
        return;
    is_end = true;
    if(my_turn)
        Opponent_win = true;
    else
        I_win = true;
}//判定是否超时3次

void Chessboard::give_up()
{
    is_end = true;
    if(my_turn)
        Opponent_win = true;
    else
        I_win = true;
    giveup = true;
    if(!has_give_up)
        emit has_clicked(-1, -1);
    has_give_up = true;
    update_round();
}//认输

void Chessboard::check_who_wins()
{
    if(I_win)
        QMessageBox::information(NULL, "提示", "我方获胜!", QMessageBox::Ok, QMessageBox::Ok);
    if(Opponent_win)
        QMessageBox::information(NULL, "提示", "对方获胜!", QMessageBox::Ok, QMessageBox::Ok);
}//判断胜负

void Chessboard::change_side()
{
    bool tmp = my_turn;
    my_turn = opponent_turn;
    opponent_turn = tmp;
    if(my_turn)
        turn_display->setText("我的回合");
    else
        turn_display->setText("对方回合");
}//改变持边
