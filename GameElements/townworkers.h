#ifndef TOWNWORKERS_H
#define TOWNWORKERS_H
#include <vector>
#include "./MapElements/fence.h"
#include "./MapElements/townhall.h"
#include "player.h"

using namespace std;

class townworkers: public Player
{
private:
    vector<pair<int,int>> path;
    pair<int,int> currentgoal;
    int currentpath=0;

public:
    void setdirection();
    townworkers(int =0, int=0);
    void direct(int,int);
    void move();
    void check();

public slots:
    void startmoving();
};

#endif // TOWNWORKERS_H
