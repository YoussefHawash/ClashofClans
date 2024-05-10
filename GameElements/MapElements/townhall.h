#ifndef TOWNHALL_H
#define TOWNHALL_H
#pragma once
#include "building.h"
class TownHall : public Building
{
public:
    TownHall(QGraphicsScene *, int, int, int, int);
};

#endif // TOWNHALL_H
