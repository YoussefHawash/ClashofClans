#include "defenseunit.h"

DefenseUnit::DefenseUnit(QGraphicsScene *scene, int x, int y,  int level)
    : level(level)
    , Building(scene, x, y)
{

    setAcceptHoverEvents(false);
    switch (level)
    {
    case 1:
        img = new QPixmap(":/Imgs/Resources/TowerTeslaa.png");
        break;
    case 2:
        img = new QPixmap(":/Imgs/Resources/Tower1.png");
        break;
    case 3:
       img = new QPixmap(":/Imgs/Resources/Tower4.png");
        break;
    case 4:
        img = new QPixmap(":/Imgs/Resources/Tower2.png");
        break;
    case 5:
       img = new QPixmap(":/Imgs/Resources/Tower3.png");
        break;
    default:
        break;
    }


    *img = img->scaled(80, 80);
    setPixmap(*img);
}
