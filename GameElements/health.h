#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QWidgetItem>
#include <QBrush>
class health : public QGraphicsRectItem {
public:
    health(int, int, int, int);
    void increasehealth(int);
    bool decreasehealth(int);
    void updateHealthBar();

private:
    int x, y;
    QGraphicsRectItem *healthrect;
    int currentHealth;
    int maxHealth;
};

#endif // HEALTH_H
