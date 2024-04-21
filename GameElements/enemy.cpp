#include "enemy.h"

Enemy::Enemy(int x, int y, int tx, int ty)
    : Player(x, y, 500, 5)
{
    int slope_x = posx-tx;
    int slope_y = posy-ty;
    dx = speed*((slope_x/sqrt(pow(slope_y,2)+pow(slope_x,2))));
    dy = speed*((slope_y/sqrt(pow(slope_x,2)+pow(slope_y,2))));
    QPixmap *img = new QPixmap(":/Imgs/Resources/icon.png");
    *img = img->scaled(80, 80);
    setPixmap(*img);

    movetime = new QTimer();
    connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
    movetime->start(100);
}

// checks whether to move or deal damage
void Enemy::check()
{

    QList<QGraphicsItem *>colliding_items =collidingItems();
    for(int i=0,n=colliding_items.size();i<n;++i)
    {
        // detecting fence
        if (Fence *fence = dynamic_cast<Fence *>(colliding_items[i])) {
            fence->reducehealth(200);
            qDebug() << fence->gethealth();
            if (fence->gethealth() <= 0) {
                delete fence;
                qDebug() << "Deleted";
            }
            return;

        }

        else if (TownHall *hall = dynamic_cast<TownHall *>(colliding_items[i])) {
            hall->reducehealth(200);
            qDebug() << hall->gethealth();
            if (hall->gethealth() <= 0) {
                delete hall;
                qDebug() << "Deleted";
            }
            return;

        }
        // detecting townhall

        //detecting townworkers
        else if (townworkers *worker = dynamic_cast<townworkers *>(colliding_items[i])) {
            //worker->reducehealth(100);
        }
    }
    setPos(x() - dx, y() - dy);
}

void Enemy::move() {}
