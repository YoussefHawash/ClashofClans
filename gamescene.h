#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QTimer>
#include "enemy.h"
class GameScene : public QGraphicsScene
{
private:
    QTimer *time;
    int map[9][16];
    int gamemode;

public:
    GameScene(int);
    void createEnemy();
};

#endif // GAMESCENE_H
