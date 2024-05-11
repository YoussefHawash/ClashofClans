#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>
#include <vector>
#include "./MapElements/fence.h"
#include "./MapElements/townhall.h"
#include "gamescene.h"
#include "player.h"
#include "townworkers.h"

using namespace std;
class Enemy : public Player
{
    Q_OBJECT
private:
    int damage;
    Building *damging;
    vector<pair<int,int>> path;
    pair<int,int> currentgoal;
    int currentpath=0;
public:
    static QTimer *HitTimer;
    void deletedamaging();
    void setdirection();
    Enemy(int, int, int, int, int);
public slots:
    void check();
    void move();
    void hitbuilding();
signals:
    void TownhallDestroyed(bool);
};

#endif // ENEMY_H
