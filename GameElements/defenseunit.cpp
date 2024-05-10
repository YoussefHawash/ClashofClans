#include "defenseunit.h"

DefenseUnit::DefenseUnit(int xfactor, int yfactor, int level)
    : level(level)
{
    type = 2;
    if (level == 1) {
        img = new QPixmap(":/Imgs/Resources/cannon.png");
    }
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
