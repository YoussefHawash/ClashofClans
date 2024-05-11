#include "townworkers.h"
townworkers::townworkers(int x, int y):Player(x,y,1000,20){
    setPos(x,y);
    QPixmap *img = new QPixmap(":/Imgs/Resources/Citizen worker.png");
    *img = img->scaled(60, 60);
    setPixmap(*img);
}

void townworkers::direct(int x, int y)
{
    targetx = x;
    targety = y;
    int slope_x = posx-targetx;
    int slope_y = posy-targety;
    dx = speed*((slope_x/sqrt(pow(slope_y,2)+pow(slope_x,2))));
    dy = speed*((slope_y/sqrt(pow(slope_x,2)+pow(slope_y,2))));
}

void townworkers::check()
{
    if(posx == targetx && posy == targety){
        QList<QGraphicsItem *>colliding_items =collidingItems();
        for(int i=0,n=colliding_items.size();i<n;++i)
        {
            // detecting fence
            if (Fence *fence = dynamic_cast<Fence*>(colliding_items[i])) {
                fence->increasehealth(20);
                return;

            }
        }
    }
    else{
        move();
    }
}

void townworkers::move(){
    setPos(x()+dx, y()+dy);
}





