#ifndef STAR_H
#define STAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimer>

class Star : public QWidget
{
    Q_OBJECT
public:
    explicit Star(QWidget *parent = 0);
    ~Star();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimer *timer_star;

    int starIndex;
    int starSize;
    bool needTransform;

signals:

private slots:
    void starTransform();
};

#endif // STAR_H
