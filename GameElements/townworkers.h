#ifndef TOWNWORKERS_H
#define TOWNWORKERS_H
#include "./MapElements/fence.h"
#include "./MapElements/townhall.h"
#include "player.h"

class townworkers: public Player
{
private:
public:
    townworkers(int =0, int=0);
    void direct(int,int);
    void move();
    void check();
};

#endif // TOWNWORKERS_H
