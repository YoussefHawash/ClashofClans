#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include<QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsEllipseItem>

class Bullet :public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:

    Bullet(int,int,int,int);
private slots:
    void shoot();
private:

    int xi,xf,yi,yf;

};



#endif // BULLET_H
