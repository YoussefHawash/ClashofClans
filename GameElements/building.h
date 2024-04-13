#ifndef BUILDING_H
#define BUILDING_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include "health.h"
class Building : public QGraphicsPixmapItem, public QObject
{
protected:
    QPixmap *img;
    health *h = nullptr;

public:
    Building();
    void SetHealth(QGraphicsScene *);
    void reducehealth(int);
    void increasehealth(int);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
};

#endif // BUILDING_H
