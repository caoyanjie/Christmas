#include "christmas.h"
#include <QDesktopWidget>
Christmas::Christmas(QWidget *parent)
    : QWidget(parent)
    ,snowCurrentCount(0)
    ,meteorToTextCount(0)
    ,snowIsShow(true)
    ,windowOnTop(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);  //拖动窗体会延迟
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);                            //出现在一个窗口上，如果该窗口最小化，本程序将再也找不着
    this->setAttribute(Qt::WA_TranslucentBackground);
    QDesktopWidget desktop;
    this->resize(desktop.width(), desktop.height());
lab_snow = new QLabel(this);
    //圣诞树
    christmasTree = new ChristmasTree(this);
    lab_merryChristmas = new QLabel(this);

    lab_merryChristmas->setGeometry(desktop.width()-292, desktop.availableGeometry().height()-72, 292, 72);
    christmasTree->move(lab_merryChristmas->x()+(lab_merryChristmas->width()-christmasTree->width())/2, lab_merryChristmas->y()-christmasTree->height());

    lab_merryChristmas->setObjectName("lab_merryChristmas");

    //星星
    for (int i=0; i<starCountDesktop; i++)
    {
        star = new Star(this);
        starList.append(star);
    }

    //定时器产生雪花

    lab_snow->resize(this->width(), this->height());
    timer_newSnow = new QTimer(this);
    timer_newSnow->start(1000);
    connect(timer_newSnow, SIGNAL(timeout()), this, SLOT(timerNewSnow()));
    christmasTree->snowIsShow = snowIsShow;

    //流星
    lab_meteor = new QLabel(this);
    lab_meteor->hide();
    lab_meteor->resize(40, 40);
    lab_meteor->setStyleSheet("border-image: url(:/Images/meteor.png);");
    animation_meteor = new QPropertyAnimation(lab_meteor, "pos");
    animation_meteor->setDuration(2000);
    connect(animation_meteor, SIGNAL(finished()), this, SLOT(hideMeteor()));
    timer_meteor = new QTimer(this);
    connect(timer_meteor, SIGNAL(timeout()), this, SLOT(meteor()));
    timer_meteor->start(5000);

    //星星组成文字
    timer_starText = new QTimer(this);
    connect(timer_starText, SIGNAL(timeout()), this, SLOT(starToText()));
    timer_starText->start(3000);

    setStyleSheet(
                "#lab_merryChristmas{"
                    "border-image: url(:/Images/MerryChristmas 1.png);"
                "}"
                );

    connect(christmasTree, SIGNAL(addStarOnDesktop()), this, SLOT(addStarOnDesktop()));
    connect(christmasTree, SIGNAL(reduceStarOnDesktop()), this, SLOT(reduceStarOnDesktop()));
    connect(christmasTree, SIGNAL(showSnow()), this, SLOT(showSnow()));
    connect(christmasTree, SIGNAL(windowStayOnTop()), this, SLOT(windowStayOnTop()));
}

Christmas::~Christmas()
{
}

//计算文字坐标
void Christmas::setTextPos(QPoint point1[], int arrayIndex, QPoint startPos, int step, Christmas::method forward)
{
    switch(forward)
    {
    case horizontal:                            //横
        for (int i=0; i<step; i++)
        {
            point1[arrayIndex++] = QPoint(startPos.x()+i*textPointSpacing, startPos.y());
        }
        break;
    case vertical:                              //竖
        for (int i=0; i<step; i++)
        {
            point1[arrayIndex++] = QPoint(startPos.x(), startPos.y()+i*textPointSpacing);
        }
        break;
    case leftFalling:                           //撇
        for (int i=0; i<step; i++)
        {
            point1[arrayIndex++] = QPoint(startPos.x()-i*(textPointSpacing/2), startPos.y()+i*(textPointSpacing));
        }
        break;
    case rightFalling:                          //捺
        for (int i=0; i<step; i++)
        {
            point1[arrayIndex++] = QPoint(startPos.x()+i*(textPointSpacing/2), startPos.y()+i*(textPointSpacing));
        }
        break;
    default:                                    //错
        qDebug() << "Wrong Method!!!";
    }
}

void Christmas::timerNewSnow()
{
    if (snowCurrentCount < snowCount)
    {
        QDesktopWidget desktop;
        //产生雪花
        snow[snowCurrentCount] = new Snow(lab_snow);
        snow[snowCurrentCount]->move(qrand()%desktop.width(), qrand()%20);
        snow[snowCurrentCount]->show();

        //动画
        animation_snow[snowCurrentCount] = new QPropertyAnimation(snow[snowCurrentCount], "pos");
        animation_snow[snowCurrentCount]->setDuration(15000);
        animation_snow[snowCurrentCount]->setStartValue(snow[snowCurrentCount]->pos());
        animation_snow[snowCurrentCount]->setEndValue(QPoint(snow[snowCurrentCount]->x(), desktop.height()));
        animation_snow[snowCurrentCount]->setLoopCount(-1);
        animation_snow[snowCurrentCount]->start();
        snowCurrentCount ++;
    }
}

//桌面增加10颗星
void Christmas::addStarOnDesktop()
{
    for (int i=0; i<10; i++)
    {
        star = new Star(this);
        star->show();
        starList.append(star);
    }
}

//桌面减少10颗星
void Christmas::reduceStarOnDesktop()
{
    int count = starList.length()<10 ? starList.length() : 10;
    for (int i=0; i<count; i++)
    {
        starList.at(starList.length()-1)->hide();
        starList.removeAt(starList.length()-1);
    }
}

//流星出现
void Christmas::meteor()
{
    QDesktopWidget desktop;
    lab_meteor->move(qrand()%(desktop.width()-100)+50, qrand()%(desktop.height()/3));
    lab_meteor->show();
    animation_meteor->setStartValue(lab_meteor->pos());
    animation_meteor->setEndValue(QPoint(lab_meteor->x()-(desktop.availableGeometry().height()-lab_meteor->y()), desktop.availableGeometry().height()));
    animation_meteor->start();
}

//流行消失
void Christmas::hideMeteor()
{
    lab_meteor->hide();
}

//星星组成文字
void Christmas::starToText()
{
    timer_starText->stop();
    //初始化文字坐标
    QDesktopWidget desktop;
    int baseX = 300;
    int baseY = desktop.availableGeometry().height()-180;
    int spacing = 6;
    int currentArrayIndex = 0;
    int arrayStep[3];
    //参数      坐标数组          起点数组下标          落笔点坐标             笔画长度         落笔走势
    //第一竖
    setTextPos(point_starText, currentArrayIndex, QPoint(baseX, baseY), arrayStep[0]=4, vertical);
    //第二横
    setTextPos(point_starText, currentArrayIndex+=arrayStep[0], QPoint(baseX+textPointSpacing, baseY), arrayStep[1]=5, horizontal);
    //第三竖
//    setTextPos(point_starText, currentArrayIndex+=arrayStep[1], QPoint(currentArrayIndex-1].x(), point_starText[currentArrayIndex-1].y()+textPointSpacing), arrayStep[0]-1, vertical);
    setTextPos(point_starText, currentArrayIndex+=arrayStep[1], QPoint(point_starText[arrayStep[0]+arrayStep[1]-1].x(), point_starText[arrayStep[0]+arrayStep[1]-1].y()+textPointSpacing), arrayStep[0]-1, vertical);
    //第四横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[0]-1), QPoint(point_starText[arrayStep[0]-1].x()+textPointSpacing, point_starText[arrayStep[0]-1].y()), arrayStep[1]-1, horizontal);
    //第五横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[1]-1), QPoint(point_starText[arrayStep[0]-1].x(), point_starText[arrayStep[0]-1].y()+textPointSpacing*2), arrayStep[1]+1, horizontal);
    //第六横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[1]+1), QPoint(point_starText[currentArrayIndex].x()-textPointSpacing*2, point_starText[currentArrayIndex].y()+textPointSpacing*3), arrayStep[1]+1+4, horizontal);
    //第七撇
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[1]+1+4), QPoint(point_starText[currentArrayIndex-(arrayStep[1]+1+4)+3+3].x(), point_starText[currentArrayIndex-(arrayStep[1]+1+4)+3+3].y()+textPointSpacing), arrayStep[2]=8, leftFalling);
    //第八捺
    setTextPos(point_starText, currentArrayIndex+=8, QPoint(point_starText[26].x(), point_starText[26].y()), arrayStep[2]-1, rightFalling);

    //第一横
    setTextPos(point_starText, currentArrayIndex+=arrayStep[2]-1, QPoint(baseX+textPointSpacing*6*2, baseY), arrayStep[3]=5, horizontal);
    //第二横
    setTextPos(point_starText, currentArrayIndex+=arrayStep[3], QPoint(baseX+textPointSpacing*6*2, baseY+textPointSpacing*2), arrayStep[3], horizontal);
    //第三竖
    setTextPos(point_starText, currentArrayIndex+=arrayStep[3], QPoint(point_starText[currentArrayIndex].x()+textPointSpacing*2, point_starText[currentArrayIndex].y()-textPointSpacing*4), arrayStep[3]+2, vertical);
    //第四横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+2), QPoint(baseX+textPointSpacing*6*2-textPointSpacing*2, baseY+textPointSpacing*4), arrayStep[3]+3, horizontal);
    //第五竖
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+3), QPoint(baseX+textPointSpacing*6*2, baseY+textPointSpacing*6), arrayStep[3]+3, vertical);
    //第六横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+3), QPoint(point_starText[currentArrayIndex].x()+textPointSpacing, point_starText[currentArrayIndex].y()), arrayStep[3]-1, horizontal);
    //第七竖
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]-1), QPoint(point_starText[(currentArrayIndex+arrayStep[3]-1-1)].x(), point_starText[(currentArrayIndex+arrayStep[3]-1)-1].y()+textPointSpacing), arrayStep[3]+3-1, vertical);
    //第八横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+3-1), QPoint(point_starText[currentArrayIndex].x()-textPointSpacing*3, point_starText[currentArrayIndex].y()+textPointSpacing), arrayStep[3]-2, horizontal);
    //第九横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]-2), QPoint(point_starText[currentArrayIndex].x(), point_starText[currentArrayIndex].y()+textPointSpacing*2), arrayStep[3]-2, horizontal);
    //第十竖
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]-2), QPoint(baseX+textPointSpacing*6*2+textPointSpacing*(arrayStep[3]+1), baseY), arrayStep[3]+2, vertical);
    //第11横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+2), QPoint(point_starText[currentArrayIndex].x()+textPointSpacing, point_starText[currentArrayIndex].y()), arrayStep[3]-1, horizontal);
    //第12竖
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]-1), QPoint(point_starText[currentArrayIndex+(arrayStep[3]-1)-1].x(), point_starText[currentArrayIndex+(arrayStep[3]-1)-1].y()+textPointSpacing), arrayStep[3]+2-1, vertical);
    //第13撇
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+2-1), QPoint(point_starText[currentArrayIndex].x()-textPointSpacing*2, point_starText[currentArrayIndex].y()+textPointSpacing*3), arrayStep[3]+1, leftFalling);
    //第14竖
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+1), QPoint(point_starText[currentArrayIndex].x(), point_starText[currentArrayIndex].y()+textPointSpacing*2), arrayStep[3]+3, vertical);
    //第15横
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]+3), QPoint(point_starText[currentArrayIndex+(arrayStep[3]+3)-1].x()+textPointSpacing, point_starText[currentArrayIndex+(arrayStep[3]+3)-1].y()), arrayStep[3]-2, horizontal);
    //第16竖
    setTextPos(point_starText, currentArrayIndex+=(arrayStep[3]-2), QPoint(point_starText[currentArrayIndex+(arrayStep[3]-2)-1].x(), point_starText[currentArrayIndex+(arrayStep[3]-2)-1].y()-textPointSpacing*2), arrayStep[3]-3, vertical);

    for (int i=0; i<133; i++)
    {
        starText[i] = new Star(this);
        starText[i]->move(point_starText[i]);
    }
    lab_meteorToText = new QLabel(this);
    lab_meteorToText->resize(22, 22);
    lab_meteorToText->setStyleSheet("border-image: url(:/Images/starToText.png);");
    animation_meteorToText = new QPropertyAnimation(lab_meteorToText, "pos");
    animation_meteorToText->setDuration(500);
    animation_meteorToText->setStartValue(QPoint(qrand()%desktop.width(), qrand()%(desktop.availableGeometry().height()/2)));
    animation_meteorToText->setEndValue(point_starText[0]);
    connect(animation_meteorToText, SIGNAL(finished()), this, SLOT(writeText()));
    lab_meteorToText->show();
    animation_meteorToText->start();
}

void Christmas::writeText()
{
    starText[meteorToTextCount++]->show();

    animation_meteorToText->setStartValue(QPoint(qrand()%this->width(), qrand()%(this->height()/2)));
    animation_meteorToText->setEndValue(point_starText[meteorToTextCount]);
    if (meteorToTextCount <= 133)
    {
        animation_meteorToText->start();
    }
    else
    {
        animation_meteorToText->deleteLater();
        //字体弹跳走动
        QDesktopWidget desktop;
        int x = desktop.width()-10-merryChristmassSize.width()-20-starText[132]->x();
        int y = desktop.availableGeometry().height()-starText[130]->y()-15;
        QPropertyAnimation *animation_textRun;
        for(int i=0; i<133; i++)
        {
            animation_textRun = new QPropertyAnimation(starText[i], "pos");
            animation_textRun->setDuration(3000);
            animation_textRun->setStartValue(starText[i]->pos());
 //           animation_textRun->setEndValue(QPoint(starText[i]->x()+500, starText[i]->y()));
            animation_textRun->setEndValue(QPoint(starText[i]->x()+x, starText[i]->y()+y));
            animation_textRun->setEasingCurve(QEasingCurve::InOutBounce);
            animation_textRun->start(QAbstractAnimation::DeleteWhenStopped);
        }
        connect(animation_textRun, SIGNAL(finished()), this, SLOT(merryChristmasFalling()));
    }
}

//圣诞快乐降落
void Christmas::merryChristmasFalling()
{
    QDesktopWidget desktop;
    QLabel *lab_merryChristmasFalling = new QLabel(this);
    lab_merryChristmasFalling->resize(merryChristmassSize);
    lab_merryChristmasFalling->setStyleSheet("border-image: url(:/Images/merryChristmas.png);");
    lab_merryChristmasFalling->show();

    QPropertyAnimation *animation_merryChristmasFalling = new QPropertyAnimation(lab_merryChristmasFalling, "pos");
    animation_merryChristmasFalling->setDuration(3000);
    animation_merryChristmasFalling->setStartValue(QPoint(desktop.width()-lab_merryChristmasFalling->width(), christmasTree->y()));
    animation_merryChristmasFalling->setEndValue(QPoint(desktop.width()-lab_merryChristmas->width()-10, desktop.availableGeometry().height()-lab_merryChristmasFalling->height()));
    animation_merryChristmasFalling->setEasingCurve(QEasingCurve::OutBounce);
    animation_merryChristmasFalling->start(QAbstractAnimation::DeleteWhenStopped);
}

//显示隐藏雪花
void Christmas::showSnow()
{
    if (snowIsShow)
    {qDebug() << "1";
        lab_snow->hide();
        snowIsShow = false;
        christmasTree->snowIsShow = false;
    }
    else
    {qDebug() << "2";
        lab_snow->show();
        snowIsShow = true;
        christmasTree->snowIsShow = true;
    }
}

void Christmas::windowStayOnTop()
{
    if (!windowOnTop)
    {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);
        this->show();
        windowOnTop = true;
        christmasTree->isOnTop = true;
    }
    else
    {
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
        this->show();
        windowOnTop = false;
        christmasTree->isOnTop = false;
    }
}
