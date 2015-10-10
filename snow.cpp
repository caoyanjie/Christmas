#include "snow.h"
#include <QPainter>

Snow::Snow(QWidget *parent) :
    QWidget(parent)
  ,snowRadius(12)
  ,angle(0)
  ,needRotate(false)
{
    add = qrand()%12;
    this->resize((snowRadius+add)*2, (snowRadius+add)*2);
    timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

//重绘事件
void Snow::paintEvent(QPaintEvent *event)
{
    QPixmap pix;
    pix.load(tr(":/Images/snow.png"));

    QPainter painter(this);
    painter.translate(this->width()/2, this->height()/2);
    if (needRotate)
    {
        painter.rotate(angle -= 5);
        needRotate = false;
    }
    else
    {
        painter.rotate(angle);
    }
    painter.drawPixmap(-(snowRadius+add), -(snowRadius+add), (snowRadius+add)*2, (snowRadius+add)*2, pix);
    if (angle <= -360)
    {
        angle = 0;
    }
}

void Snow::timeout()
{
    needRotate = true;
    update();
}
