#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


class Player : public QGraphicsPixmapItem, public QObject
{
   // Q_OBJECT
protected:
    int health;
    int speed;
    int posx ;
    int posy ;
    int targetx=0,targety =0;
    int vol=40;
    float dx;
    float dy;

    QTimer *movetime;
public:
    Player(int,int,int,int);
    void getdamage();
    bool die();
};

#endif // PLAYER_H
