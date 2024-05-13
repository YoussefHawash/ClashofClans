#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include "building.h"
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
    Building *HittingItem;
    vector<Node> path;
    Node currentgoal;
    int currentpath=1;
    vector<vector<Node *> > *map;

public:
    static QTimer *movetime;
    Player(int,int,int,int);
    health *gethealth();
    struct CostComparator
    {
        bool operator()(const pair<float, Node> &a, const pair<float, Node> &b) const
        {
            return a.first > b.first;
        }
    };

    vector<Node> Dijekstra(const Node &start, const Node &goal);
};

#endif // PLAYER_H
