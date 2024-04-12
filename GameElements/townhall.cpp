#include "townhall.h"

TownHall::TownHall(int xfactor, int yfactor)
{
    img = new QPixmap(":/Imgs/Resources/townhall.jpg");
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
