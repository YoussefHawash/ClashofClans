#include "player.h"

QTimer* Player::movetime = new QTimer;

Player::Player(int x, int y, int hp, int s)
    : posx(x)
    , posy(y)
    , speed(s)
{
    h = new health(posx, posy, pixmap().width(), hp);
    setPos(x,y);
   movetime->start(s);
}

health *Player::gethealth()
{
    return h;
}
