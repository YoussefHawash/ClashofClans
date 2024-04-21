#include "fence.h"

Fence::Fence(int xfactor, int yfactor, std::vector<int> a)
{
    // img = new QPixmap(":/Imgs/Resources/fence.png");
    // *img = img->scaled(xfactor / 4, yfactor / 4);
    // setPixmap(*img);
    QPixmap pixmap1(":/Imgs/Resources/fence.png");
    pixmap1 = pixmap1.scaled(xfactor / 8, yfactor / 8);
    // Load the second image

    // Create a combined pixmap
    QPixmap combinedPixmap(80, 80);
    combinedPixmap.fill(Qt::transparent);

    // Paint the first image onto the combined pixmap
    QPainter painter(&combinedPixmap);
    painter.drawPixmap(35, 35, pixmap1);

    // Paint the second image onto the combined pixmap
    //henAAAAA4
    QPixmap wall(":/Imgs/Resources/wall.png");
    for (int var = 0; var < a.size(); ++var) {
        if (a[var] == 0) {
            wall = wall.scaled(10, 35);
            painter.drawPixmap(35, 0, wall);
        }
        if (a[var] == 1) {
            wall = wall.scaled(35, 10);
            painter.drawPixmap(45, 35, wall);
        }
        if (a[var] == 2) {
            wall = wall.scaled(10, 35);
            painter.drawPixmap(35, 45, wall);
        }
        if (a[var] == 3) {
            wall = wall.scaled(35, 10);
            painter.drawPixmap(0, 35, wall);
        }
    }
    setPixmap(combinedPixmap);
}
