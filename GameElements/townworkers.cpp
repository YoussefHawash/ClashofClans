#include "townworkers.h"
#include "gamescene.h"
extern GameScene *gamescene;
townworkers::townworkers(int x, int y):Player(x,y,1000,20){
    setPos(x,y);
    homex=x;
    homey=y;
    QPixmap *img = new QPixmap(":/Imgs/Resources/Citizen worker.png");
    *img = img->scaled(60, 60);
    setPixmap(*img);
}

void townworkers::direct(int x, int y)
{
    path = Dijekstra(*(gamescene->map)[int((y - 1) / 80)][int((x - 1) / 80)],
                     *(gamescene->map)[int(y / 80)][int(x / 80)]);

    directed =1;
    setgoals();
}

void townworkers::check()
{
    if(x() == targetx && y() == targety){
        QList<QGraphicsItem *>colliding_items =collidingItems();
        for(int i=0,n=colliding_items.size();i<n;++i)
        {
            // detecting fence
            if (Fence *fence = dynamic_cast<Fence*>(colliding_items[i])) {
                if(fence->gethealth()->gethealth() > 80){
                    fence->gethealth()->increasehealth(4);
                    return;

                }
                if (Fence *fence = dynamic_cast<Fence*>(colliding_items[i])) {
                    if(fence->gethealth()->gethealth() <= 80){
                        directed =0;
                        direct(homex,homey);
                        return;

                    }

                }
            }
        }


    }
    move();
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


