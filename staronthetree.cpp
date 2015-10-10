#include "staronthetree.h"

StarOnTheTree::StarOnTheTree(int z, QWidget *parent) : QWidget(parent)
  ,starsCount(120)
  ,starsFallingCount(50)
{
    underTheTree = under;
    div = z;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(500);
}

StarOnTheTree::~StarOnTheTree()
{

}

void StarOnTheTree::timeout()
{
    switch(div)
    {
    case 0:                                 //在树后面
        if (starList.length() >= starsCount)
        {
            timer->deleteLater();
            return;
        }
        for (int i=0; i<5; i++)
        {
            star = new Star(this);
            star->move(qrand()%(this->width()/2+star->width())+this->width()/2, qrand()%(this->height()));
            star->show();
            animation = new QPropertyAnimation(star, "pos");
            animation->setDuration(qreal(star->x()/qreal(this->width())*8000));
            animation->setStartValue(star->pos());
            animation->setEndValue(QPoint(star->x()-200, star->y()+200));
            animation->setLoopCount(-1);
            animation->start();

            starList.append(star);
            animationList.append(animation);
        }
        break;
    case 1:                                  //在树前面
        if (starList.length() >= starsCount)
        {
            timer->deleteLater();
            return;
        }
        for (int i=0; i<5; i++)
        {
            star = new Star(this);
            star->move(qrand()%(this->width()/2-star->width()), qrand()%(this->height()));
            star->show();
            animation = new QPropertyAnimation(star, "pos");
            animation->setDuration(qreal((this->width()-star->x())/qreal(this->width())*8000));
            animation->setStartValue(star->pos());
            animation->setEndValue(QPoint(star->x()+200, star->y()+200));
            animation->setLoopCount(-1);
            animation->start();

            starList.append(star);
            animationList.append(animation);
        }
        break;
    case 2:                                  //在树前面下落
        if (starList.length() >= starsFallingCount)
        {
            timer->deleteLater();
            return;
        }
        for (int i=0; i<5; i++)
        {
            star = new Star(this);
            star->move(qrand()%this->width(), -star->height());
            star->show();
            animation = new QPropertyAnimation(star, "pos");
            animation->setDuration(qreal(this->height()-star->y())/qreal(this->width())*8000);
            animation->setStartValue(star->pos());
            animation->setEndValue(QPoint(star->x(), this->height()));
            animation->setLoopCount(-1);
            animation->start();

            starList.append(star);
            animationList.append(animation);
        }
        break;
    case 3:                                  //在树头旋转
        if (starList.length() >= 50)
        {
            timer->deleteLater();
            return;
        }
        for (int i=0; i<3; i++)
        {
            star = new Star(this);
            star->move(-star->width(), qrand()%this->height());
            star->show();
            animation = new QPropertyAnimation(star, "pos");
            animation->setDuration(8000);
            animation->setStartValue(star->pos());
            animation->setEndValue(QPoint(this->width()+star->width(), star->height()));
            animation->setLoopCount(-1);
            animation->start();

            starList.append(star);
            animationList.append(animation);
        }
        break;
    case 4:                                  //在树头旋转
        if (starList.length() >= 50)
        {
            timer->deleteLater();
            return;
        }
        for (int i=0; i<3; i++)
        {
            star = new Star(this);
            star->move(this->width()+star->width(), qrand()%this->height());
            star->show();
            animation = new QPropertyAnimation(star, "pos");
            animation->setDuration(8000);
            animation->setStartValue(star->pos());
            animation->setEndValue(QPoint(-star->width(), star->height()));
            animation->setLoopCount(-1);
            animation->start();

            starList.append(star);
            animationList.append(animation);
        }
        break;
    }
}

