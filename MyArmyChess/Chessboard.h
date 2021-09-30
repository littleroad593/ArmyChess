#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <QPushButton>
#include <cmath>
#include <algorithm>
#include "Chesspiece.h"

struct railway_pos
{
    int x, y, num;
    bool has_checked;
};

class Chessboard : public QWidget
{
    Q_OBJECT
public:
    explicit Chessboard(QWidget *parent = nullptr);
    ~Chessboard();
    void mousePressEvent(QMouseEvent *e);
    void click_chesspiece(int x, int y, bool signal = true, int a = -1);
    int select_a_chesspiece(int x, int y);
    bool cangoto(int c1, int x, int y);
    bool chess_in_the_way(int c1, int x, int y);
    bool chess_in_the_field(int ID);
    bool red_no_mine();
    bool blue_no_mine();
    bool all_cannot_move(bool color);
    bool chess_in_the_next_pos(int ID);
    bool on_railway(int x, int y);
    void compare_chess();
    void update_round(int ID = -1);
    void decide_color(int ID);
    void setRailway();
    void search_way_for_gongbing(int n1, int x, int y);
    void overtime_lose(int overtime);
    void check_who_wins();
    int set_first_turn(int a = -1);
    void change_side();

    QLabel* round_counter;
    QLabel* turn_display;
    QLabel* color_display;
    QLabel* time_left;
    QLabel* Myovertime;
    QLabel* Opponentovertime;
    QPushButton *give_up_button;
    QVector<Chesspiece*> chesspieces;
    int c1 = -1, c2 = -1;
    bool I_win = false;
    bool Opponent_win = false;
    bool flag = false;//工兵可移动标志
    bool has_give_up = false;
    bool has_connected = false;
    bool start = false;
    int red_counter[12] = {1, 3, 1, 1, 2, 2, 2, 2, 3, 3, 3, 2};//红方死亡计数
    int blue_counter[12] = {1, 3, 1, 1, 2, 2, 2, 2, 3, 3, 3, 2};//蓝方死亡计数
    QVector<bool> my_color, opponent_color;

private:
    const int chess_x[5] = {19, 138, 257, 376, 495};
    const int chess_y[12] = {13, 68, 123, 178, 233, 288, 451, 506, 561, 616, 671, 726};
    const int chess_length = 75, chess_height = 38;
    QVector<railway_pos> *v;
    QTimer* timer = new QTimer;
    int round = 0;
    int second = 0;
    int my_overtime = 0, opponent_overtime = 0;
    bool is_end = false;
    bool my_turn;
    bool opponent_turn;
    bool has_decided_color = false;
    bool giveup = false;

signals:
    void has_clicked(int x, int y, int a = -1);

public slots:
    void update_time_counter();
    void give_up();
};

#endif // CHESSBOARD_H
