#ifndef SNOW_H
#define SNOW_H

#include <QWidget>
#include <QEvent>
#include <QTimer>

class Snow : public QWidget
{
    Q_OBJECT
public:
    explicit Snow(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTimer *timer;
    int snowRadius;
    int add;
    int angle;
    bool needRotate;

signals:

private slots:
    void timeout();
};

#endif // SNOW_H
