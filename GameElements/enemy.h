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
    QTimer *checked;
    Enemy(int, int, int, int);

public slots:
    void check();
    void move();
};

#endif // ENEMY_H
