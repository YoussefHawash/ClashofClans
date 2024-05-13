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
#include "GameElements/townworkers.h"
#include "node.h"
using namespace std;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:


    //HUD
    QGraphicsTextItem *TimeInfo;
    QGraphicsTextItem *WaveInfo;
    QGraphicsTextItem *TogglePause;
    QGraphicsTextItem *BoostInfo;
    QGraphicsTextItem *Navigation;
    QGraphicsTextItem *GameOverText;
    // Next wave ( HUD )
    QGraphicsPixmapItem *EventWindow;
    QGraphicsTextItem *NextwaveText;
    QGraphicsTextItem *NextwaveTextNav;
    //All timers
    QTimer *EnemyCreation = new QTimer();
    QTimer *Wavetimer;
    QTimer* BoosterCreationTimer;
    QTimer *BoosterIntervalTimer;
    //Map_Objects
    TownHall *townhall;
    DefenseUnit *Cannon;
    townworkers *townworker1;
    townworkers *townworker2;
    // x and y factors
    int yfactor, xfactor;
    //Variables
    int Wavenum;
    int WaveTime;
    int CreationFrequency;
    int gamelevel;
    int BoostTime=10;
    bool BoosterActivated=false;
    // Ability to click on the scene
    bool clickable;

public:
     vector<Fence*> fences;
    GameScene(int, double, double);
    void disconnectTimers();
    void RenderingMap();
    void StartWave();
    void MoveToNextLevel();
    void clearEnemies();
    void shoot(const QPointF &mousePos);
    //Handling Inputs
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    //Map & Map Objects
    vector<vector<Node *> > map;
    TownHall *gettownhall();
public slots:
    void BoosterActivate();
    void Gameover(bool);
    void EndWave();
    void createEnemy();
    void TogglePauseFunc();
    void createBooster();
    void BoosterCountDown();
    void checkfences();
signals:
    void ReturnMainMenu();
};

#endif // GAMESCENE_H


