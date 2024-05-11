#ifndef DEFENSEUNIT_H
#define DEFENSEUNIT_H
#include "building.h"
class DefenseUnit : public Building
{
private:
    int level;
    float damage;

public:
    DefenseUnit(int, int, int);
};

#endif // DEFENSEUNIT_H
