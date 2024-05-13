#include "enemy.h"
#include "townworkers.h"
#include <QTimer>
extern GameScene *gamescene;
QTimer *Enemy::HitTimer= new QTimer;


Enemy::Enemy(int x, int y, int d, int s, int hitspeed)
    : Player(x, y, 60, 100)
    , damage(d),hitting_speed(hitspeed)
{
    motion1 = new QPixmap(":/Imgs/Resources/motion1.png");
    motion2 = new QPixmap(":/Imgs/Resources/motion2.png");
    motion3 = new QPixmap(":/Imgs/Resources/motion3.png");
    *motion1=motion1->scaled(40, 40);
    *motion2=motion2->scaled(40, 40);
    *motion3=motion3->scaled(40, 40);
    setPixmap(*motion1);
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
        else if (townworkers *townwork = dynamic_cast<townworkers *>(colliding_items[i])) {

            townwork->dead=true;
            townwork->hide();
            return;
        }
    }
    Animate();
    move();
}
void Enemy::setgoals()
{

    if(currentpath<path.size()){
    currentgoal.x=(path[currentpath].y*80);
    currentgoal.y=(path[currentpath].x*80);
    int slope_x = x() -  (currentgoal.x+40);
    int slope_y = y() -  (currentgoal.y+40);
    dx = 10 * ((slope_x / sqrt(pow(slope_y, 2) + pow(slope_x, 2))));
    dy = 10 * ((slope_y / sqrt(pow(slope_x, 2) + pow(slope_y, 2))));
    currentpath++;}
};
void Enemy::move() {


    setPos(x()-dx,y()-dy);
    QPointF desiredPosition(currentgoal.x+40, currentgoal.y+40);
    double distance = QLineF(pos(), desiredPosition).length();
    double  tolerance =1*(sqrt(pow(dx,2)+pow(dy,2)));
    // Check if the distance is within the tolerance radius
    if (distance <= tolerance) {
    setgoals();

    }



}

void Enemy::hitbuilding()
{
    HittingItem->gethealth()->decreasehealth(damage);
    if (HittingItem->gethealth()->gethealth() <= 0) {
        if (typeid(*(HittingItem)) == typeid(TownHall)){
            emit TownhallDestroyed(0);
        } else {
            HittingItem->hide();
            HittingItem->gethealth()->hide();
            gamescene->map[int(HittingItem->y()/80)][int(HittingItem->x()/80)]->makeitgrass(gamescene->map[int(HittingItem->y()/80)][int(HittingItem->x()/80)]->weight=1+sqrt(pow(int((gamescene->gettownhall()->y()/80)/80)-int(HittingItem->y()/80),2)+pow(int(gamescene->gettownhall()->x()/80)-int(HittingItem->x()/80),2)));
            // path = Dijekstra(*(gamescene->map)[int((y() - 1) / 80)][int((x() - 1) / 80)],
            //                  *(gamescene->map)[int(gamescene->gettownhall()->y() / 80)][int(gamescene->gettownhall()->x()  / 80)]);
            }
            disconnect(HitTimer, SIGNAL(timeout()), this, SLOT(hitbuilding()));
            connect(movetime, SIGNAL(timeout()), this, SLOT(check()));

    }
}

void Enemy::Animate()
    {

    if(phase==1)
        {

        setPixmap(*motion2); phase=2;
        }
    else if (phase==2)
    {
        phase=3;
            setPixmap(*motion3);
        }
        else if (phase==3){
            phase=1;
            setPixmap(*motion1);}
};
