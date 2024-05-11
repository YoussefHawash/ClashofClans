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
    int xi, xf, yi, yf;

public:
    Bullet(int,int,int,int);
    void CheckCollide();
private slots:
    void Move();
signals:
    void BoosterActivate();
};

#endif // BULLET_H
