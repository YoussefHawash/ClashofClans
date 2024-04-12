#ifndef HUD_H
#define HUD_H
#include <QApplication>
#include <QAudioOutput>
#include <QBoxLayout>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSizePolicy>
#include "gamescene.h"
#include "mainmenu.h"
class HUD :  public QGraphicsView
{
    Q_OBJECT
private:
    QApplication *App;
    MainMenu *MainUI;
    GameScene *gamescene;
    QMediaPlayer *Sound;
    QAudioOutput *audioOutput;

public:
    HUD(QApplication * = nullptr);
    void DisplayMainMenu();
    ~HUD();

public slots:
    void NewGame();
    void RandomGame();
    void StoryMode();
    void Exit();
};
#endif // HUD_H
