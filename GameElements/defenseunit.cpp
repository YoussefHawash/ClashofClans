#include "defenseunit.h"

DefenseUnit::DefenseUnit(int xfactor, int yfactor, int level)
    : level(level)
{
    if (level == 1) {
        img = new QPixmap(":/Imgs/Resources/cannon.jpg");
        damage = 10;
    }
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
