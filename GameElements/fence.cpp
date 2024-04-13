#include "fence.h"

Fence::Fence(int xfactor, int yfactor)
{
    img = new QPixmap(":/Imgs/Resources/fence.png");
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
