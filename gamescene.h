#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include "GameElements/bullet.h"
#include "GameElements/defenseunit.h"
#include "GameElements/fence.h"
#include "GameElements/grass.h"
#include "GameElements/townhall.h"
#include <vector>
using namespace std;
class GameScene : public QGraphicsScene
{
private:
    QTimer *time;
    vector<vector<int>> map;

    int gamemode;
    //i can loop in the items and get hte coordinates
    int x_cannon, y_cannon;

public:
    GameScene(double, double, int);
    void DisplayMap();

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void shoot(const QPointF &mousePos);
};

#endif // GAMESCENE_H
