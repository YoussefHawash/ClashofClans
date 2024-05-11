#ifndef GAMESCENE_H
#define GAMESCENE_H
#pragma once
#include <QAudioOutput>
#include <QDebug>
#include <QEventLoop>
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QRandomGenerator>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include "GameElements/MapElements/defenseunit.h"
#include "GameElements/MapElements/fence.h"
#include "GameElements/MapElements/townhall.h"
#include "GameElements/bullet.h"
#include "GameElements/enemy.h"
#include "GameElements/townworkers.h"
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    // Next wave
    QGraphicsPixmapItem *EventWindow;
    QGraphicsTextItem *NextwaveText;
    QGraphicsTextItem *NextwaveTextNav;
    //HUD
    QGraphicsTextItem *TimeInfo;
    QGraphicsTextItem *WaveInfo;
    QGraphicsTextItem *TogglePause;
    //All timers
    QTimer *EnemyCreation = new QTimer();
    QTimer *Wavetimer;
    //Townhall_Object
    TownHall *townhall;
    DefenseUnit *Cannon;
    //Map
    vector<vector<int> > map;
    // x and y factors
    int yfactor, xfactor;
    //Variables
    int Wavenum;
    int WaveTime;
    int CreationFrequency = 4000;
    int gamelevel;
    // Ability to click on the scene
    bool clickable;

public:
    GameScene(int, double, double);
    void MoveToNextLevel();
    void RenderingMap();
    void start();
    void clearEnemies();
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void shoot(const QPointF &mousePos);
public slots:
    void Gameover(bool);
    void EndWave();
    void createEnemy();
    void TogglePauseFunc();
signals:
    void ReturnMainMenu();
};

#endif // GAMESCENE_H


