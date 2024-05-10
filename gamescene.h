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
    // Next wave view
    QPushButton *NextWaveButton;
    QGraphicsTextItem *NextwaveText;
    QGraphicsProxyWidget *Move_Next_Wave;

    int Wavenum=1;
    QTimer *EnemyCreation = new QTimer();
    QTimer *Wavetimer;
    TownHall *townhall;
    QGraphicsTextItem *WaveTime;
    QGraphicsTextItem *WaveLabel;
    vector<vector<Building *> > map;
    int timeleft;
    int Creationtime = 4000;
    // Ability to click on the scene
    bool clickable;
    // Important Coordiantes
    int x_cannon, y_cannon;
    int x_townhall, y_townhall;
    // x and y factors
    int yfactor, xfactor;

public:
    GameScene(double, double);
    void RenderingMap();
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void shoot(const QPointF &mousePos);
    void clearEnemies();
    void start();
public slots:
    void Gameover();
    void Return_to_Menu();
    void EndWave();
    void createenemy();
};

#endif // GAMESCENE_H


