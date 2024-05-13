#include "townworkers.h"
#include "gamescene.h"
extern GameScene *gamescene;
townworkers::townworkers(int x, int y):Player(x,y,1,100){
    setPos(x,y);
    QPixmap *img = new QPixmap(":/Imgs/Resources/Citizen worker.png");
    *img = img->scaled(40, 40);
    setPixmap(*img);
    Repairing=new QTimer();
    Repairing->start(1000);
}

void townworkers::check()
{
             QList<QGraphicsItem *>colliding_items =collidingItems();
            for(int i=0,n=colliding_items.size();i<n;++i)
            {
                 if( Target==colliding_items[i])
                {
                    Repair();
                     disconnect(movetime, SIGNAL(timeout()), this, SLOT(check()));
                    connect(Repairing,SIGNAL(timeout()), this, SLOT(Repair()));
                }
                 else if (Avaliable &&  gamescene->gettownhall()==colliding_items[i])
                 {
                     hide();
                     return;
                 }


            }


        move();
}

void townworkers::Repair()
{
    if(!CheckDirections())
    {

        Target->gethealth()->increasehealth(10);
    }

}




void townworkers::move() {
    setPos(x() - dx, y() - dy);

}

void townworkers::SetTarget(Fence *target)
{

    Avaliable=false;
    Target=target;
    Target->On_Repair =true;
    int slope_x = x() -  Target->x();
    int slope_y = y() -  Target->y();
    dx = 20 * ((slope_x / sqrt(pow(slope_y, 2) + pow(slope_x, 2))));
    dy = 20 * ((slope_y / sqrt(pow(slope_x, 2) + pow(slope_y, 2))));
    connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
}
void townworkers::GoHome(){
    int slope_x = x() -  gamescene->gettownhall()->x();
    int slope_y = y() -  gamescene->gettownhall()->y();
    dx = 20 * ((slope_x / sqrt(pow(slope_y, 2) + pow(slope_x, 2))));
    dy = 20 * ((slope_y / sqrt(pow(slope_x, 2) + pow(slope_y, 2))));
}
bool townworkers::CheckDirections()
{
    if(dead)
    {

        return 1;
    }
    if(!Target->isVisible() )
    {
        //IF Destroyed
        Avaliable=true;
        Target->On_Repair =false;
        GoHome();
        connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
        disconnect(Repairing,SIGNAL(timeout()), this, SLOT(Repair()));
        return 1;
    }
    else if(typeid(*(Target)) == typeid(Fence) && Target->gethealth()->gethealth()==80)
    {
        //IF Healed
        Target->On_Repair =false;
        Avaliable=true;
        GoHome();
        connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
        disconnect(Repairing,SIGNAL(timeout()), this, SLOT(Repair()));
        return 1;
    }
    return 0;
};
