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
#include <vector>

#include "GameElements/townhall.h"

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
    vector<vector<Building *> > map;
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
    void GameEnd(bool);
    void EndWave();
    void createEnemy();
signals:
    void ReturnMainMenu();
};

#endif // GAMESCENE_H


