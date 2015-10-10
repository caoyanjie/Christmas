#ifndef CHRISTMAS_H
#define CHRISTMAS_H

#include <QWidget>
#include "christmastree.h"
#include "snow.h"
const int snowCount = 30;
const int starCountDesktop = 100;
const QSize merryChristmassSize = QSize(292, 72);

class Christmas : public QWidget
{
    Q_OBJECT

public:
    Christmas(QWidget *parent = 0);
    ~Christmas();

    bool snowIsShow;

private:
    ChristmasTree *christmasTree;
    QLabel *lab_merryChristmas;

    //雪花
    QLabel *lab_snow;
    Snow *snow[snowCount];


    //星星
    Star *star;
    QList<Star *> starList;
    QPropertyAnimation *animation_snow[snowCount];

    QTimer *timer_newSnow;
    int snowCurrentCount;

    //流星
    QLabel *lab_meteor;
    QTimer *timer_meteor;
    QPropertyAnimation *animation_meteor;

    //星星组成文字
    enum method{
        horizontal,     //横
        vertical,       //竖
        leftFalling,    //撇
        rightFalling    //捺
    };
    Star *starText[133];
    QLabel *lab_meteorToText;
    QPropertyAnimation *animation_meteorToText;
    QPoint point_starText[133];
    QTimer *timer_starText;
    const int textPointSpacing = 8;                     //文字笔画中星星的间隔
    int meteorToTextCount;
    void setTextPos(QPoint point_starText[], int arrayIndex, QPoint startPos, int step, method forward);

    //窗口最前
    bool windowOnTop;

public slots:
    //窗口最前
    void windowStayOnTop();

private slots:
    void timerNewSnow();
    void addStarOnDesktop();
    void reduceStarOnDesktop();

    //流星
    void meteor();
    void hideMeteor();

    //星星组成文字
    void starToText();
    void writeText();

    //圣诞快乐降落
    void merryChristmasFalling();

    //显示/隐藏雪花
    void showSnow();
};

#endif // CHRISTMAS_H
