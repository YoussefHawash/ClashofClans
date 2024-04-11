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
    MainMenu *mainmenu;
    GameScene *game;
    QMediaPlayer *sound;
    QAudioOutput *audioOutput;

public:
    HUD(QApplication * = nullptr);
    void DisplayMainMenu();

    ~HUD();

public slots:
    void newgame();
    void randomgame();
    void storymode();
    void exit();
};
#endif // HUD_H
