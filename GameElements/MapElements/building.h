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
    bool On_Repair=false;
    Building(QGraphicsScene *, int , int );
    void SetHealth(int);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    health* gethealth();

};

#endif // BUILDING_H
