#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "health.h"
#include "node.h"
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
    int dx;
    int dy;
public:
    static QTimer *movetime;
    Player(int,int,int,int);
    health *gethealth();
    struct CostComparator
    {
        bool operator()(const std::pair<float, Node> &a, const std::pair<float, Node> &b) const
        {
            return a.first > b.first;
        }
    };

    std::vector<Node> Dijekstra(const Node &start, const Node &goal);
};

#endif // PLAYER_H
