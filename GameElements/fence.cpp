#include "fence.h"

Fence::Fence(int xfactor, int yfactor)
{
    img = new QPixmap(":/Imgs/Resources/fence.jpg");
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
