#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QWidgetItem>
#include <QBrush>
class health : public QGraphicsRectItem {
public:
    health(int);
    void increasehealth(int);
    bool decreasehealth(int);
    void updateHealthBar();
private:
    QGraphicsRectItem *healthrect;
    int currentHealth;
    int maxHealth;
};

#endif // HEALTH_H
