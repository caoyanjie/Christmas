#ifndef CHRISTMASTREE_H
#define CHRISTMASTREE_H

#include <QWidget>
#include <QLabel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QApplication>
#include "staronthetree.h"
const int starCountOnTree = 200;

class ChristmasTree : public QWidget
{
    Q_OBJECT
public:
    explicit ChristmasTree(QWidget *parent = 0);

    bool snowIsShow;
    bool isOnTop;

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel *lab_christmasTree;
    QLabel *lab_lightLeft;
    QLabel *lab_lightRight;

    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    QTimer *timer;

    //星星
    StarOnTheTree *starOnTheTree;
    int treeWidth;
    int treeHeight;
    int leftColor;
    int rightColor;
    int velocity_star;
    int velocity_light;

    bool autoRun;
    QPoint offset;

signals:
    void addStarOnDesktop();
    void reduceStarOnDesktop();
    void showSnow();
    void windowStayOnTop();

private slots:
    void quit();
    void previous();
    void next();
    void pause();
    void mute();
    void onTop();
    void timeout();

    void addStarOnTree();

    //设置透明度
    void setOpacityTen();
    void setOpacityTwenty();
    void setOpacityThirty();
    void setOpacityForty();
    void setOpacityFifty();
    void setOpacitySixty();
    void setOpacitySeventy();
    void setOpacityEighty();
    void setOpacityNinety();
    void setOpacityHundred();
};

#endif // CHRISTMASTREE_H
