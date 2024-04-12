#ifndef GRASS_H
#define GRASS_H
#include "building.h"
class Grass : public Building
{
public:
    Grass();
    virtual bool IsMovable() { return 0; };
};

#endif // GRASS_H
