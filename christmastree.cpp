#include "christmastree.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QFileInfo>
#include <QDebug>
ChristmasTree::ChristmasTree(QWidget *parent) :
    QWidget(parent)
  ,treeWidth(200)
  ,treeHeight(310)
  ,leftColor(1)
  ,rightColor(5)
  ,velocity_star(8000)
  ,velocity_light()
  ,isOnTop(false)
  ,snowIsShow(true)
{
    this->resize(treeWidth,treeHeight);
    this->setWindowOpacity(0.2);

    //圣诞树后面星星
    starOnTheTree = new StarOnTheTree(0, this);
//    starOnTheTree->setGeometry(5, 0, this->width()-10, this->height()/2);
    starOnTheTree->setGeometry(5, 0, this->width(), this->height()/2);

    //圣诞树头上星星
    starOnTheTree = new StarOnTheTree(4, this);
    starOnTheTree->setGeometry(0, 0, this->width(), 60);


    //圣诞树，左彩灯，右彩灯
    lab_christmasTree = new QLabel(this);
    lab_lightLeft = new QLabel(this);
    lab_lightRight = new QLabel(this);

    lab_christmasTree->resize(treeWidth, treeHeight);
    lab_lightLeft->resize(treeWidth, treeHeight);
    lab_lightRight->resize(treeWidth, treeHeight);

    //圣诞树前面星星
    starOnTheTree = new StarOnTheTree(1, this);
    starOnTheTree->setGeometry(0, 0, this->width(), this->height()/2);

    //圣诞树头上星星
    starOnTheTree = new StarOnTheTree(3, this);
    starOnTheTree->setGeometry(0, 0, this->width(), 60);

    //圣诞树前下落的星星
    starOnTheTree = new StarOnTheTree(2, this);
    starOnTheTree->setGeometry(5, this->height()/2-20, this->width()-10, this->height()/2);
    starOnTheTree->setStyleSheet("background: red;");

    lab_christmasTree->setObjectName(tr("lab_christmasTree"));
    lab_lightLeft->setObjectName(tr("lab_lightLeft"));
    lab_lightRight->setObjectName(tr("lab_lightRight"));

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist;
    player->setPlaylist(playlist);

    ///playlist->addMedia(QUrl(tr("%1/mediaservice/christmas.mp3").arg(QFileInfo("").absoluteFilePath())));
    playlist->addMedia(QUrl(tr("christmas.mp3")));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->play();

    setStyleSheet(
                "#lab_christmasTree{"
                    "border-image: url(:/Images/christmasTree.png);"
                "}"
                "#lab_lightLeft{"
                    "border-image: url(:/Images/light1.png);"
                "}"
                "#labs_lightRight{"
                    "border-image: url(:/Images/light5.png);"
                "}"
                "QMenu{"
                    "background: rgba(0, 0, 0, 120);"
                "}"
                "#lab_merryChristmas{"
                    "border-image: url(:/Images/MerryChristmas 1.png);"
                "}"
                );

    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), SLOT(timeout()));
}

//上下文菜单事件
void ChristmasTree::contextMenuEvent(QContextMenuEvent *event)
{
    //透明度菜单
    QMenu menu_opacity;
    menu_opacity.setTitle("设置透明度");
    menu_opacity.addAction(tr("10%"), this, SLOT(setOpacityTen()));
    menu_opacity.addAction(tr("20%"), this, SLOT(setOpacityTwenty()));
    menu_opacity.addAction(tr("30%"), this, SLOT(setOpacityThirty()));
    menu_opacity.addAction(tr("40%"), this, SLOT(setOpacityForty()));
    menu_opacity.addAction(tr("50%"), this, SLOT(setOpacityFifty()));
    menu_opacity.addAction(tr("60%"), this, SLOT(setOpacitySixty()));
    menu_opacity.addAction(tr("70%"), this, SLOT(setOpacitySeventy()));
    menu_opacity.addAction(tr("80%"), this, SLOT(setOpacityEighty()));
    menu_opacity.addAction(tr("90%"), this, SLOT(setOpacityNinety()));
    menu_opacity.addAction(tr("100%"), this, SLOT(setOpacityHundred()));

    QMenu menu;menu.addMenu(&menu_opacity);
    menu.addAction(QIcon(":/Images/previous.png"), tr("音乐上一曲"), this, SLOT(previous()));
    menu.addAction(QIcon(":/Images/next.png"), tr("音乐下一曲"), this, SLOT(next()));
    menu.addAction(QIcon(":/Images/pause.png"), tr("音乐暂停"), this, SLOT(pause()));
    menu.addAction(QIcon(tr("%1").arg(player->isMuted() ? ":/Images/ok.png" : ":/Images/mute.png")), tr("静音"), this, SLOT(mute()));
    menu.addAction(tr("桌面 +10颗星"), this, SIGNAL(addStarOnDesktop()));
    menu.addAction(tr("桌面 -10颗星"), this, SIGNAL(reduceStarOnDesktop()));
    menu.addAction(QIcon(tr("%1").arg(snowIsShow ? ":/Images/ok.png" : "")), tr("显示雪花"), this, SIGNAL(showSnow()));
//    menu.addAction(QIcon(""), tr("圣诞树 +10颗星"), this, SLOT(addStarOnTree()));
//    menu.addAction(QIcon(""), tr("圣诞树 -10颗星"), this, SLOT(addStarOnTree()));
//    menu.addAction(QIcon(""), tr("星星眨眼频率+"), this, SLOT(addStarOnTree()));
//    menu.addAction(QIcon(""), tr("星星眨眼频率-"), this, SLOT(addStarOnTree()));
//    menu.addAction(QIcon(""), tr("圣诞树闪灯频率+"), this, SLOT(addStarOnTree()));
//    menu.addAction(QIcon(":/Images/exit1.png"), tr("圣诞树闪灯频率-"), this, SLOT(addStarOnTree()));
    menu.addAction(QIcon(tr("%1").arg(isOnTop ? ":/Images/ok.png" : ":/Images/onTop.png")), tr("窗口最前"), this, SIGNAL(windowStayOnTop()));
    menu.addAction(QIcon(tr("%1").arg(autoRun ? ":/Images/ok.png" : "")), tr("开机自启"), this, SLOT());
    menu.addAction(QIcon(":/Images/exit.png"), tr("退出"), this, SLOT(quit()));
    menu.exec(event->globalPos());
}

//鼠标按下事件
void ChristmasTree::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        offset = event->globalPos() - pos();
    }
}

//鼠标移动事件
void ChristmasTree::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        this->move(event->globalPos() - offset);
    }
}

//退出
void ChristmasTree::quit()
{
    qApp->exit();
}

//上一曲
void ChristmasTree::previous()
{
    playlist->previous();
}

//下一曲
void ChristmasTree::next()
{
    playlist->next();
}

//暂停
void ChristmasTree::pause()
{
    switch(player->state())
    {
    case QMediaPlayer::PausedState:
        player->play();
        break;
    default:
        player->pause();
    }
}

//静音
void ChristmasTree::mute()
{
    player->setMuted(player->isMuted() ? false : true);
}

//窗口最顶层
void ChristmasTree::onTop()
{/*
    this->parentWidget()->window()->
    this->parentWidget()->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);
    qDebug() << this->parentWidget()->pos() << this->parentWidget()->size();
    this->parentWidget()->show();
    */
}

//定时器溢出
void ChristmasTree::timeout()
{
    lab_lightLeft->setStyleSheet(tr("border-image: url(:/Images/light%1.png);").arg(leftColor++));
    lab_lightRight->setStyleSheet(tr("border-image: url(:/Images/light%1.png);").arg(rightColor++));
    if (leftColor == 5)
    {
        leftColor = 1;
    }
    if (rightColor == 9)
    {
        rightColor = 5;
    }
}

//圣诞树增加10颗星
void ChristmasTree::addStarOnTree()
{

}

//设置透明度为 10%
void ChristmasTree::setOpacityTen()
{
    this->parentWidget()->setWindowOpacity(0.1);
}
//设置透明度为 10%
void ChristmasTree::setOpacityTwenty()
{
    this->parentWidget()->setWindowOpacity(0.2);
}
//设置透明度为 10%
void ChristmasTree::setOpacityThirty()
{
    this->parentWidget()->setWindowOpacity(0.3);
}
//设置透明度为 10%
void ChristmasTree::setOpacityForty()
{
    this->parentWidget()->setWindowOpacity(0.4);
}
//设置透明度为 10%
void ChristmasTree::setOpacityFifty()
{
    this->parentWidget()->setWindowOpacity(0.5);
}
//设置透明度为 10%
void ChristmasTree::setOpacitySixty()
{
    this->parentWidget()->setWindowOpacity(0.6);
}
//设置透明度为 10%
void ChristmasTree::setOpacitySeventy()
{
    this->parentWidget()->setWindowOpacity(0.7);
}
//设置透明度为 10%
void ChristmasTree::setOpacityEighty()
{
    this->parentWidget()->setWindowOpacity(0.8);
}
//设置透明度为 10%
void ChristmasTree::setOpacityNinety()
{
    this->parentWidget()->setWindowOpacity(0.9);
}
//设置透明度为 10%
void ChristmasTree::setOpacityHundred()
{
    this->parentWidget()->setWindowOpacity(1);
}
