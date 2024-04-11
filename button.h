#ifndef BUTTON_H
#define BUTTON_H
#include <QString>
#include <QBrush>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
class button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QGraphicsTextItem *text;
public:
    button(QString name,QGraphicsItem* parent = NULL);
    void mousePressEvent(QGraphicsSceneMouseEvent* Event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* Event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* Event);
signals:
    void clicked();

};

#endif // BUTTON_H
