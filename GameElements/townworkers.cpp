#include "townworkers.h"
#include "gamescene.h"
extern GameScene *gamescene;
QTimer *townworkers::HealTimer= new QTimer;
townworkers::townworkers(int x, int y):Player(x,y,1000,20){
    setPos(x,y);
    homex=x;
    homey=y;
    QPixmap *img = new QPixmap(":/Imgs/Resources/Citizen worker.png");
    *img = img->scaled(60, 60);
    setPixmap(*img);
}

void townworkers::direct(int a, int b)
{
    path = Dijekstra(*(gamescene->map)[int((y() - 1) / 80)][int((x() - 1) / 80)],
                     *(gamescene->map)[int(a / 80)][int(b / 80)]);
    connect(movetime,SIGNAL(timeout()),this,SLOT(check()));
    disconnect(HealTimer,SIGNAL(timeout()),this,SLOT(Heal()));
    HealTimer->start(1000);
    directed =1;
    setgoals();
}

void townworkers::check()
{
        QList<QGraphicsItem *>colliding_items =collidingItems();
        for(int i=0,n=colliding_items.size();i<n;++i)
        {

            // detecting fence
            if (Fence *fence = dynamic_cast<Fence*>(colliding_items[i])) {
                f=fence;
                connect(HealTimer,SIGNAL(timeout()),this,SLOT(Heal()));
                disconnect(movetime,SIGNAL(timeout()),this,SLOT(check()));

                }




    }
        move();
}

void townworkers::Heal()
{
    if(f->gethealth()->gethealth() < 80){
        f->gethealth()->increasehealth(5);
        return;

    }
    if(f->gethealth()->gethealth() <= 80){
        disconnect(HealTimer,SIGNAL(timeout()),this,SLOT(Heal()));
        directed =0;
        dx=0;
        dy=0;
        return;

    }

}



void townworkers::setgoals()
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
void townworkers::move() {
    setPos(x() - dx, y() - dy);
    qDebug() << "Current "<<currentgoal.x<< currentgoal.y;
    qDebug() <<dx<<dy;
    if ((x()>currentgoal.x&& x()<(currentgoal.x+80))||(y()>currentgoal.y && y()<(currentgoal.y+80)))
    {
        setgoals();
    }



}


