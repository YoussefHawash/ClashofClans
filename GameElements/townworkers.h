#ifndef TOWNWORKERS_H
#define TOWNWORKERS_H
#include "player.h"
#include "fence.h"
#include "townhall.h"

class townworkers: public Player
{
private:
public:
    townworkers(int =0, int=0);
    void direct(int,int);
    void move();
    void fix();
    void check();
};

#endif // TOWNWORKERS_H
