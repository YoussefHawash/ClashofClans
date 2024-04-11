#include "button.h"

button::button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // rect details
    setRect(0,0,200,50);
    QBrush yellow;
    yellow.setStyle(Qt::SolidPattern);
    yellow.setColor(Qt::yellow);
    setBrush(yellow);

    // button text
    text =  new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    setAcceptHoverEvents(true);
}

void button::mousePressEvent(QGraphicsSceneMouseEvent *Event)
{
    emit clicked();
}

void button::hoverEnterEvent(QGraphicsSceneHoverEvent *Event)
{
    // change color
    QBrush blue;
    blue.setStyle(Qt::SolidPattern);
    blue.setColor(Qt::blue);
    setBrush(blue);
}

void button::hoverLeaveEvent(QGraphicsSceneHoverEvent *Event)
{
    // change color
    QBrush yellow;
    yellow.setStyle(Qt::SolidPattern);
    yellow.setColor(Qt::yellow);
    setBrush(yellow);
}
