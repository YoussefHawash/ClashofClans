#include "enemy.h"
#include <QTimer>
extern GameScene *gamescene;
QTimer *Enemy::HitTimer= new QTimer;


Enemy::Enemy(int x, int y, int d, int s, int hitspeed)
    : Player(x, y, 60, s)
    , damage(d),hitting_speed(hitspeed)
{
    QPixmap *img = new QPixmap(":/Imgs/Resources/icon.png");
    *img = img->scaled(50, 50);
    setPixmap(*img);
    int slope_x = posx - gamescene->gettownhall()->x();
    int slope_y = posy -  gamescene->gettownhall()->y();
    dx = 20 * ((slope_x / sqrt(pow(slope_y, 2) + pow(slope_x, 2))));
    dy = 20 * ((slope_y / sqrt(pow(slope_x, 2) + pow(slope_y, 2))));
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
            HittingItem = fence;
            disconnect(movetime, SIGNAL(timeout()), this, SLOT(check()));
            connect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            HitTimer->start(hitting_speed);
            return;
        }
        else if (TownHall *hall = dynamic_cast<TownHall *>(colliding_items[i])) {
            HittingItem = hall;
            disconnect(movetime, SIGNAL(timeout()), this, SLOT(check()));
            connect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            HitTimer->start(hitting_speed);
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
    HittingItem->gethealth()->decreasehealth(damage);
    if (HittingItem->gethealth()->gethealth() <= 0) {
        if (typeid(*(HittingItem)) == typeid(TownHall)){
            emit TownhallDestroyed(0);
        } else {
            HittingItem->hide();
            disconnect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
        }
    }
}

