#include "grass.h"

Grass::Grass(int xfactor, int yfactor)
{
    setZValue(-1);
    img = new QPixmap(":/Imgs/Resources/GrassChunk.jpg");
    *img = img->scaled(xfactor, yfactor);
    setPixmap(*img);
}
