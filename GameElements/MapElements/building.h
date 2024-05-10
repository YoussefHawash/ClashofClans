#ifndef BUILDING_H
#define BUILDING_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "../health.h"
class Building : public QGraphicsPixmapItem, public QObject
{
protected:
    QGraphicsScene *mainscene;
    QPixmap *img;
    health *h;

public:
    Building(QGraphicsScene *, int x, int y);
    void SetHealth(int);
    void decreasehealth(int);
    void increasehealth(int);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    int gethealth();
    int gettype();
};

#endif // BUILDING_H
