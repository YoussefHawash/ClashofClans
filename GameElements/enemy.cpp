#include "enemy.h"
#include <QTimer>
Enemy::Enemy(int x, int y, int x_tower, int y_tower, int d)
    : Player(x, y, 600, 5)
    , damage(d)
{
    QPixmap *img = new QPixmap(":/Imgs/Resources/icon.png");
    *img = img->scaled(50, 50);
    setPixmap(*img);
    int slope_x = posx - x_tower;
    int slope_y = posy - y_tower;
    dx = speed * ((slope_x / sqrt(pow(slope_y, 2) + pow(slope_x, 2))));
    dy = speed * ((slope_y / sqrt(pow(slope_x, 2) + pow(slope_y, 2))));
    connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
}




// checks whether to move or deal damage
void Enemy::check()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        HitTimer = new QTimer;
        // detecting fence
        if (Fence *fence = dynamic_cast<Fence *>(colliding_items[i])) {
            damging = fence;
            disconnect(movetime, SIGNAL(timeout()), this, SLOT(check()));

            connect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            HitTimer->start(1000);
            return;

        }
        else if (TownHall *hall = dynamic_cast<TownHall *>(colliding_items[i])) {
            damging = hall;
            disconnect(movetime, SIGNAL(timeout()), this, SLOT(check()));
            connect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            HitTimer->start(1000);
            return;
        }
    }
    move();
}

void Enemy::move() {
    setPos(x() - dx, y() - dy);
}

void Enemy::hitbuilding()
{
    damging->decreasehealth(damage);
    if (damging->gethealth() <= 0) {
        if (typeid(*(damging)) == typeid(TownHall))
            emit TownhallDestroyed(0);
        else
            delete damging;
        disconnect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
        connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
    }
}
