#include "townhall.h"

TownHall::TownHall(int xfactor, int yfactor)
{
    type = 1;
    img = new QPixmap(":/Imgs/Resources/townhall.png");
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}


