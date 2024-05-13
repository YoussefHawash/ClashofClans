#ifndef TOWNWORKERS_H
#define TOWNWORKERS_H
#include "./MapElements/fence.h"
#include "MapElements/fence.h"
#include "player.h"

class townworkers: public Player
{
    Q_OBJECT
private:
    Building* Target;
     QTimer *Repairing;
public:
     bool dead;
    bool Avaliable=1;
    townworkers(int =0, int=0);
    void GoHome();
    bool CheckDirections();
    void move();
public slots:
    void SetTarget(Fence *);

    void check();
    void Repair();



};

#endif // TOWNWORKERS_H

