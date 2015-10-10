#include "star.h"
#include <QPainter>

Star::Star(QWidget *parent) : QWidget(parent)
  ,starIndex(1)
  ,starSize(19)
  ,needTransform(false)
{
    this->resize(starSize, starSize);
    this->move(qrand()%parentWidget()->width(), qrand()%(parentWidget()->height()/2));
    this->setStyleSheet("background: blue;");

    timer_star = new QTimer(this);
    connect(timer_star, SIGNAL(timeout()), this, SLOT(starTransform()));
    timer_star->start(200);

    starIndex = qrand() % 6 + 1;
}

Star::~Star()
{

}

void Star::paintEvent(QPaintEvent *event)
{
    QPixmap pix;
    if (needTransform)
    {
        pix.load(tr(":/Images/star%1.png").arg(++starIndex));
        needTransform = false;
    }
    else
    {
        pix.load(tr(":/Images/star%1.png").arg(starIndex));
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, starSize, starSize, pix);
    if (starIndex >= 6)
    {
        starIndex = 1;
    }
}

void Star::starTransform()
{
    needTransform = true;
    this->update();
}

