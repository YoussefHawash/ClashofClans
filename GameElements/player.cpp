#include "player.h"

QTimer* Player::movetime = new QTimer;


Player::Player(int x, int y, int hp, int s)
    : posx(x)
    , posy(y)
    , speed(s)
{
    h = new health(posx, posy, pixmap().width(), hp);
    setPos(x,y);
}

health *Player::gethealth()
{
    return h;
}
void Player::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(0.8);
    if (h != nullptr)
        h->show();
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void Player::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(1);
    if (h != nullptr)
        h->hide();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}
