#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <vector>
#include <cstdlib>
#include <ctime>

class Chesspiece : public QLabel
{
    Q_OBJECT
public:
    explicit Chesspiece(QWidget *parent = nullptr);
    ~Chesspiece();

    int turnover(int a = -1);
    int getChessID();
    bool is_red();
    bool Is_dead = false;
    bool Is_open = false;

    static std::vector<QString> paths;
    static std::vector<QString> create_paths();

private:
    int chess_ID;
    bool Is_red;

};

#endif // CHESSPIECE_H
