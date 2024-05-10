#ifndef DEFENSEUNIT_H
#define DEFENSEUNIT_H
#include "building.h"
class DefenseUnit : public Building
{
private:
    int level;
    float damage;

public:
    DefenseUnit(QGraphicsScene *, int, int, int, int, int);
    int getdamage();
};

#endif // DEFENSEUNIT_H
