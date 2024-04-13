#include "townworkers.h"
townworkers::townworkers(int x, int y):Player(x,y,50,20){
}

void townworkers::direct(int x, int y)
{
    targetx = x;
    targety = y;
    int slope_x = posx-targetx;
    int slope_y = posy-targety;
    dx = speed*((slope_x/sqrt(pow(slope_y,2)+pow(slope_x,2))));
    dy = speed*((slope_y/sqrt(pow(slope_x,2)+pow(slope_y,2))));
    QPixmap *img = new QPixmap(":/Imgs/Resources/icon.png");
    *img = img->scaled(80, 80);
    setPixmap(*img);
    movetime = new QTimer();
    QObject::connect(movetime, SIGNAL(timeout()), this, SLOT(check()));
    movetime->start(500);
}

void townworkers::check()
{
    if(posx == targetx && posy == targety){
        if(fix()){

        }
        else{
            //QObject::disconnect(time, SIGNAL(timeout()),this,SLOT(check()));
        }
    }
    else{
        move();
    }
    // QList<QGraphicsItem *>colliding_items =collidingItems();
    // for(int i=0,n=colliding_items.size();i<n;++i)
    // {
    //     // detecting fence
    //     if (Fence *fence = dynamic_cast<Fence*>(colliding_items[i])) {
    //         fence->reducehealth(100);
    //         return;

    //     }
    //     // detecting townhall
    //     else if (TownHall *town = dynamic_cast<TownHall*>(colliding_items[i])) {
    //         town->reducehealth(100);
    //         return;

    //     }
    //     // detecting townworkers
    //     // else if (TownHall *town = dynamic_cast<TownHall*>(colliding_items[i])) {
    //     //     town->reducehealth(100);
    //     // }
    // }
}

void townworkers::move(){
    setPos(x()+dx, y()+dy);
}

bool townworkers::fix(){
    // QList<QGraphicsItem *>colliding_items =collidingItems();
    // for(int i=0,n=colliding_items.size();i<n;++i)
    // {
    //     // detecting fence
    //     if (Fence *fence = dynamic_cast<Fence*>(colliding_items[i])) {
    //         fence->reducehealth(100);
    //         return;

    //     }
    //     // detecting townhall
    //     else if (TownHall *town = dynamic_cast<TownHall*>(colliding_items[i])) {
    //         town->reducehealth(100);
    //         return;

    //     }
}



