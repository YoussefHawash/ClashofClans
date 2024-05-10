#include "defenseunit.h"

DefenseUnit::DefenseUnit(QGraphicsScene *scene, int x, int y, int xfactor, int yfactor, int level)
    : level(level)
    , Building(scene, x, y)
{
    setAcceptHoverEvents(false);
    if (level == 1) {
        img = new QPixmap(":/Imgs/Resources/cannon.png");
    }
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
