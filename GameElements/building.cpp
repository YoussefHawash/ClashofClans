#include "building.h"
Building::Building()
{
    type = 0;
    setAcceptHoverEvents(true);
}

void Building::SetHealth(QGraphicsScene *a, int max)
{
    h = new health(x(), y(), pixmap().width(), max);
    a->addItem(h);
    h->hide();
}

void Building::decreasehealth(int i)
{
    h->decreasehealth(i);
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

int Building::gethealth()
{
    if(h==nullptr)
        return 0;
    return h->gethealth();
}
int Building::gettype()
{
    return type;
}
