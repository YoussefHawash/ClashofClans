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
    void decreasehealth(int);
    void updateHealthBar();
    int gethealth();

private:
    int x, y;
    int currentHealth;
    int maxHealth;
};

#endif // HEALTH_H
