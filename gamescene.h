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
    QGraphicsProxyWidget *EndWaveWidget;
    QPushButton *NextWaveButton;
    QGraphicsTextItem *NextwaveText;
    //Display Elements
    QGraphicsTextItem *TimeInfo;
    QGraphicsTextItem *WaveInfo;
    //All timers
    QTimer *EnemyCreation = new QTimer();
    QTimer *Wavetimer;
    //Townhall_Object
    TownHall *townhall;
    //Map
    vector<vector<int> > map;
    // x and y factors
    int yfactor, xfactor;
    //Variables
    int Wavenum;
    int WaveTime;
    int CreationFrequency = 4000;
    // Ability to click on the scene
    bool clickable;
    // Important Coordiantes
    int x_cannon, y_cannon;

public:
    GameScene(double, double);
    void RenderingMap();
    void clearEnemies();
    void start();
    //Check Again!!!! Shooting in defenese unit
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void shoot(const QPointF &mousePos);
public slots:
    void Gameover(bool);
    void EndWave();
    void createEnemy();
signals:
    void ReturnMainMenu();
};

#endif // GAMESCENE_H


