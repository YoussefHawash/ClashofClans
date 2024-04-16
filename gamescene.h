#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include "GameElements/bullet.h"
#include "GameElements/defenseunit.h"
#include "GameElements/fence.h"
#include "GameElements/grass.h"
#include "GameElements/townhall.h"
#include "GameElements/enemy.h"
#include <vector>
using namespace std;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QTimer *time;
    vector<vector<int>> map;

    int gamemode;
    //i can loop in the items and get hte coordinates
    int x_cannon, y_cannon;
    int x_townhall, y_townhall;

public:
    GameScene(double, double, int);
    void DisplayMap();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void shoot(const QPointF &mousePos);
public slots:
    void createenemy();
};

#endif // GAMESCENE_H
