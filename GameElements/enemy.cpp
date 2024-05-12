#include "enemy.h"
#include <QTimer>
extern GameScene *gamescene;
QTimer *Enemy::HitTimer= new QTimer;


Enemy::Enemy(int x, int y, int d, int s, int hitspeed)
    : Player(x, y, 60, 200)
    , damage(d),hitting_speed(hitspeed)
{

    QPixmap *img = new QPixmap(":/Imgs/Resources/icon.png");
    *img = img->scaled(40, 40);
    setPixmap(*img);

    path = Dijekstra(*(gamescene->map)[int((y - 1) / 80)][int((x - 1) / 80)],
                     *(gamescene->map)[int(gamescene->gettownhall()->y() / 80)][int(gamescene->gettownhall()->x()  / 80)]);

    setgoals();
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
void Enemy::setgoals()
{

    if(currentpath<path.size()){
    qDebug() << "True";
    currentgoal.x=(path[currentpath].y*80)+30;
    currentgoal.y=(path[currentpath].x*80)+30;
    int slope_x = x() -  currentgoal.x;
    int slope_y = y() -  currentgoal.y;
    dx = 20 * ((slope_x / sqrt(pow(slope_y, 2) + pow(slope_x, 2))));
    dy = 20 * ((slope_y / sqrt(pow(slope_x, 2) + pow(slope_y, 2))));
    currentpath++;}
};
void Enemy::move() {
    setPos(x() - dx, y() - dy);
    qDebug() << "Current "<<currentgoal.x<< currentgoal.y;
    qDebug() <<dx<<dy;
    if ((x()>currentgoal.x&& x()<(currentgoal.x+80))||(y()>currentgoal.y && y()<(currentgoal.y+80)))
    {
          setgoals();
      }



}

void Enemy::hitbuilding()
{
    HittingItem->gethealth()->decreasehealth(damage);
    if (HittingItem->gethealth()->gethealth() <= 0) {
        if (typeid(*(HittingItem)) == typeid(TownHall)){
            // emit TownhallDestroyed(0);
        } else {
            HittingItem->hide();
            if(HittingItem->isVisible()){
            gamescene->map[int(HittingItem->y()/80)][int(HittingItem->x()/80)]->setweight(-24);
            path = Dijekstra(*(gamescene->map)[int((y() - 1) / 80)][int((x() - 1) / 80)],
                             *(gamescene->map)[int(gamescene->gettownhall()->y() / 80)][int(gamescene->gettownhall()->x()  / 80)]);}
            disconnect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
        }
    }
}


