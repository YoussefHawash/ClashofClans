#include "bullet.h"
#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QtMath>

using namespace std;


Bullet::Bullet(int xi_pos,int yi_pos,int xf_pos,int yf_pos)
{
    xi=xi_pos;
    yi= yi_pos;
    xf= xf_pos;
    yf=  yf_pos;
    setBrush(Qt::red);
    setRect(xi_pos,yi_pos,15,10);



    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (shoot()));
    timer->start(50);
}

void Bullet::shoot()
{
    const int Vel = 20;



    double dx = Vel*(((xf-xi)/sqrt(pow((yf-yi),2)+pow((xf-xi),2))));

    double dy = Vel*(((yf-yi)/sqrt(pow((yf-yi),2)+pow((xf-xi),2))));

    setPos(x()+dx, y()+dy);


    //     if(y() < 0  || y() > scene()->height() || x() < 0 || x() > scene()->width()) {
    //         scene()->removeItem(this);
    //         delete this;
    // }
}
