#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QTimer>
#include "building.h"
#include "enemy.h"

using namespace std;
class GameScene : public QGraphicsScene
{
private:
    QTimer *time;
    int map[9][16];
    int gamemode;

public:
    GameScene(double, double, int);
    void createEnemy();
    void DisplayMap();
};

#endif // GAMESCENE_H
