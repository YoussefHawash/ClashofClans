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
    QTimer *timer;
    QTimer *Wavetimer;

    //int wavenum =3;
    string massage;
    vector<vector<int>> map;
    TownHall *a;
    int gamemode;
    //i can loop in the items and get hte coordinates
    int x_cannon, y_cannon;
    int x_townhall, y_townhall;

public:
    GameScene(double, double, int);
    void DisplayMap();
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void shoot(const QPointF &mousePos);
    void start();
    void Gameover();

public slots:
    void startwave();
    void checkwin();
    void createenemy();
};

#endif // GAMESCENE_H
