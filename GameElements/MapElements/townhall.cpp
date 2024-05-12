#include "townhall.h"

TownHall::TownHall(QGraphicsScene *scene, int x, int y)
    : Building(scene, x, y)
{
    img = new QPixmap(":/Imgs/Resources/townhall.png");
    *img = img->scaled(80, 80);
    setPixmap(*img);
    SetHealth(100);
}


