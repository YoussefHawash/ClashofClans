#include "townhall.h"

TownHall::TownHall(QGraphicsScene *scene, int x, int y, int xfactor, int yfactor)
    : Building(scene, x, y)
{
    img = new QPixmap(":/Imgs/Resources/townhall.png");
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
    SetHealth(100);
}


