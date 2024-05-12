#ifndef TOWNWORKERS_H
#define TOWNWORKERS_H
#include "./MapElements/fence.h"
#include "./MapElements/townhall.h"
#include "MapElements/fence.h"
#include "player.h"

class townworkers: public Player
{
    Q_OBJECT
private:
    Fence* f;
    int homex,homey;
    static QTimer *HealTimer;
public:
    bool directed=0;
    townworkers(int =0, int=0);
    void setgoals();
    void direct(int,int);
    void move();
public slots:
    void check();
    void Heal();



};

#endif // TOWNWORKERS_H

