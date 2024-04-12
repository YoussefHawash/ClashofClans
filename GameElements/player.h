#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player : public QGraphicsPixmapItem, public QObject
{
protected:
    int health;

public:
    Player(int);
    void getdamage();
    bool die();
};

#endif // PLAYER_H
