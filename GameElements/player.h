#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "health.h"

class Player : public QGraphicsPixmapItem, public QObject
{
    // Q_OBJECT
protected:
    health *h = nullptr;
    int damage;
    int speed;
    int posx ;
    int posy ;
    int targetx;
    int targety;
    int vel;
    float dx;
    float dy;
public:
    void startmove();
    void stopmove();
    static QTimer *movetime;
    Player(int,int,int,int);
    health *gethealth();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
};

#endif // PLAYER_H
