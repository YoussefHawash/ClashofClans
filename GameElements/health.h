#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QWidgetItem>
#include <QBrush>
class health : public QGraphicsRectItem
{
private:
    int x, y;
    float currentHealth;
    float maxHealth;
    double originalwidth;

public:
    health(int, int, int, int);
    void increasehealth(int);
    void decreasehealth(int);
    void updateHealthBar();
    int gethealth();
};

#endif // HEALTH_H
