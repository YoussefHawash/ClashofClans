#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>
#include "./MapElements/fence.h"
#include "./MapElements/townhall.h"
#include "gamescene.h"
#include "player.h"
#include "townworkers.h"
#include "node.h"
class Enemy : public Player
{
    Q_OBJECT
private:
    int damage;
    int hitting_speed;
    Building *HittingItem;
    vector<Node> path;
    Node currentgoal;
    int currentpath=1;
     vector<vector<Node *> > *map;

public:
    Enemy(int, int, int, int, int);
    static QTimer *HitTimer;
    void setgoals();
public slots:
    void check();
    void move();
    void hitbuilding();
signals:
    void TownhallDestroyed(bool);
};

#endif // ENEMY_H
