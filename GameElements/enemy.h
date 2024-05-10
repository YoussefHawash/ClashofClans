#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>
#include "./MapElements/fence.h"
#include "./MapElements/townhall.h"
#include "gamescene.h"
#include "player.h"
#include "townworkers.h"

class Enemy : public Player
{
    Q_OBJECT
private:
    int damage;
    Building *damging;

public:
    QTimer *HitTimer;

    Enemy(int, int, int, int, int);
public slots:
    void check();
    void move();
    void hitbuilding();
signals:
    void TownhallDestroyed(bool);
};

#endif // ENEMY_H
