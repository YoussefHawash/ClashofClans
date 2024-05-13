#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include<QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsEllipseItem>
#include "booster.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int xi, xf, yi, yf,damagebullet;
    int Velocity;
    bool boost;
    QPixmap *img;

public:
    Bullet(int,int,int,int,bool);
    void CheckCollide();
private slots:
    void Move();
signals:
    void BoostHit();
};

#endif // BULLET_H
