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
#include "booster.h"
#include "nodes.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <random>
#include <vector>
using namespace std;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    struct CostComparator
    {
        bool operator()(const std::pair<float, Nodes> &a, const std::pair<float, Nodes> &b) const
        {
            return a.first > b.first;
        }
    };
    GameScene(int, double, double);
    void MoveToNextLevel();
    void RenderingMap();
    vector<Nodes> Dijekstra(const Nodes &, const Nodes &);
    void start();
    void clearEnemies();
    vector<vector<Nodes *> > *getmap();

    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void shoot(const QPointF &mousePos);

private:
    // Next wave
    QGraphicsPixmapItem *EventWindow;
    QGraphicsTextItem *NextwaveText;
    QGraphicsTextItem *NextwaveTextNav;
    //HUD
    QGraphicsTextItem *TimeInfo;
    QGraphicsTextItem *WaveInfo;
    QGraphicsTextItem *TogglePause;
    QGraphicsTextItem *BoostInfo;
    QGraphicsTextItem *Navigation;
    QGraphicsTextItem *gameOverText;
    //All timers
    QTimer *EnemyCreation = new QTimer();
    QTimer *Wavetimer;
    QTimer* BoosterTimer;
    //Townhall_Object
    TownHall *townhall;
    DefenseUnit *Cannon;
    //Map
    vector<vector<Nodes *> > map;
    // x and y factors
    int yfactor, xfactor;
    //Variables
    int Wavenum;
    int WaveTime;
    int CreationFrequency;
    int gamelevel;
    int BoostTime=0;
    bool boost;
    // Ability to click on the scene
    bool clickable;

public slots:
    void Gameover(bool);
    void EndWave();
    void createEnemy();
    void TogglePauseFunc();
    void createBooster();
    void BoostTimer();
    void ActivateBooster();
signals:
    void ReturnMainMenu();
};

#endif // GAMESCENE_H


