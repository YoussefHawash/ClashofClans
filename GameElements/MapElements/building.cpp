#include "building.h"
Building::Building(QGraphicsScene *scene, int x, int y)
    : mainscene(scene)
    , h(nullptr)
{
    setAcceptHoverEvents(true);
    setPos(x, y);
}

void Building::SetHealth(int max)
{
    h = new health(x(), y(), pixmap().width(), max);
    mainscene->addItem(h);
    h->hide();
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

health* Building::gethealth()
{

    return h;
}
