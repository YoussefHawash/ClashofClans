#include "booster.h"

Booster::Booster(int x,int y) {

    setPos(x, y);
    QPixmap img;
    img = QPixmap(":/Imgs/Resources/Coin.png").scaled(50, 50);
    setPixmap(img);
}
