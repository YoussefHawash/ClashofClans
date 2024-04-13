#ifndef ENEMY_H
#define ENEMY_H

#include <QTimer>
#include <QObject>
#include "fence.h"
#include "townhall.h"
#include "townworkers.h"
#include "player.h"

class Enemy : public Player
{
    Q_OBJECT
private:
    // The dimentions of the troop


public:
    Enemy(int, int, int , int);
    void move();
    void getdamage();
    void check();
};

#endif // ENEMY_H
