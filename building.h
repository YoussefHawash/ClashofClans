#ifndef BUILDING_H
#define BUILDING_H

#include <QGraphicsPixmapItem>
#include <QObject>
class Building : public QGraphicsPixmapItem, public QObject
{
private:
public:
    Building();
    virtual bool IsMovable() { return 1; };

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
    {
        setOpacity(0.5);
        QGraphicsPixmapItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
        setOpacity(1);
        QGraphicsPixmapItem::hoverLeaveEvent(event);
    }
};

#endif // BUILDING_H
