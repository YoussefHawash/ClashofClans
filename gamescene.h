#ifndef GAMESCENE_H
#define GAMESCENE_H
#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QEventLoop>
#include <QtMultimedia/QMediaPlayer>
#include <QAudioOutput>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include "GameElements/bullet.h"
#include "GameElements/defenseunit.h"
#include "GameElements/fence.h"
#include "GameElements/grass.h"
#include "GameElements/townhall.h"
#include "GameElements/enemy.h"
#include "GameElements/townworkers.h"
#include <vector>
using namespace std;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QTimer *EnemyCreation;
    vector<vector<int>> map;
    int x_cannon, y_cannon;
    int x_townhall, y_townhall;
    QGraphicsTextItem *WaveTime;
    int timeleft;
    bool clickable;

public:
    GameScene(double, double);
    void DisplayMap();
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void shoot(const QPointF &mousePos);
    void start();
    void Gameover();

public slots:
    void EndWave();
    void createenemy();
};

#endif // GAMESCENE_H
