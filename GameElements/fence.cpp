#include "fence.h"

Fence::Fence(int xfactor, int yfactor, std::vector<int> a)
{
    QPixmap pixmap1(":/Imgs/Resources/fence.png");
    pixmap1 = pixmap1.scaled(xfactor / 4, yfactor / 4);
    // Load the second image

    // Create a combined pixmap
    QPixmap combinedPixmap(80, 80);
    combinedPixmap.fill(Qt::transparent);
    //WhiteSpaces
    float gap = (80 - (xfactor / 4)) / 2;
    // Paint the first image onto the combined pixmap
    QPainter painter(&combinedPixmap);
    painter.drawPixmap(gap, gap, pixmap1);

    // Paint the second image onto the combined pixmap
    //henAAAAA4
    QPixmap wall(":/Imgs/Resources/fence.png");
    for (int var = 0; var < a.size(); ++var) {
        if (a[var] == 0) {
            wall = wall.scaled(10, 30);
            painter.drawPixmap(gap + 5, 0, wall);
        }
        if (a[var] == 1) {
            wall = wall.scaled(30, 10);
            painter.drawPixmap(50, gap + 5, wall);
        }
        if (a[var] == 2) {
            wall = wall.scaled(10, 30);
            painter.drawPixmap(gap + 5, 50, wall);
        }
        if (a[var] == 3) {
            wall = wall.scaled(30, 10);
            painter.drawPixmap(0, gap + 5, wall);
        }
    }
    setPixmap(combinedPixmap);
}
