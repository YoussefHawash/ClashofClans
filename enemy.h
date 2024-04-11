#ifndef ENEMY_H
#define ENEMY_H

#include <QTimer>
#include "player.h"

class Enemy : public Player
{
private:
    // The dimentions of the troop
    int posx = -1;
    int posy = -1;
    QTimer *movetime;

public:
    Enemy(int, int);
    void move();
    void getdamage();
    void dealdamage();
};

#endif // ENEMY_H
