#ifndef STARONTHETREE_H
#define STARONTHETREE_H

#include <QWidget>
#include "star.h"
#include <QPropertyAnimation>
enum div
{
    under,
    front,
    falling
};
class StarOnTheTree : public QWidget
{
    Q_OBJECT
public:
    explicit StarOnTheTree(int z, QWidget *parent = 0);
    ~StarOnTheTree();

private:
    bool underTheTree;
    Star *star;
    QPropertyAnimation *animation;
    QList<Star*> starList;
    QList<QPropertyAnimation *> animationList;
    QTimer *timer;
    const int starsCount;
    const int starsFallingCount;
    int div;

signals:

private slots:
    void timeout();
};

#endif // STARONTHETREE_H
