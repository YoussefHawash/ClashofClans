#include "building.h"
using namespace std;
Building::Building()
{
    setAcceptHoverEvents(true);
}

void Building::SetHealth(QGraphicsScene *a)
{
    h = new health(x(), y(), pixmap().width(), 500);
    a->addItem(h);
    h->hide();
    qDebug() << x();
}

void Building::reducehealth(int i)
{
    if(h->decreasehealth(i)){
    }
    else{
        delete this;
    }
}

void Building::increasehealth(int i)
{
    h->increasehealth(i);
}
void Building::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(0.8);
    if (h != nullptr)
        h->show();
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void Building::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setOpacity(1);
    if (h != nullptr)
        h->hide();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

