#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "health.h"
#include "nodes.h"
#include <vector>
using namespace std;
class Player : public QGraphicsPixmapItem, public QObject
{
    // Q_OBJECT
protected:
    health *h = nullptr;
    int damage;
    int speed;
    int posx ;
    int posy ;
    int targetx;
    int targety;
    int vel;
    float dx;
    float dy;
public:
    struct CostComparator
    {
        bool operator()(const std::pair<float, Nodes> &a, const std::pair<float, Nodes> &b) const
        {
            return a.first > b.first;
        }
    };
    void startmove();
    void stopmove();
    static QTimer *movetime;
    Player(int, int, int, int);
    health *gethealth();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    std::vector<Nodes> Dijekstra(const Nodes &start, const Nodes &goal);
};

#endif // PLAYER_H
