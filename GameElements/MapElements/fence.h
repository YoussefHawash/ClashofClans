#ifndef FENCE_H
#define FENCE_H
#include "building.h"
#include <vector>

class Fence : public Building
{
public:
    Fence(QGraphicsScene *, int, int, std::vector<int>);
};

#endif // FENCE_H
