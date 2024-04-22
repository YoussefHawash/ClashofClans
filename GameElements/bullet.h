#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include<QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsEllipseItem>

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
};

#endif // BULLET_H
