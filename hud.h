#ifndef HUD_H
#define HUD_H

#include <QApplication>
#include <QGraphicsView>
#include <QMainWindow>
#include "gamescene.h"
#include "mainmenu.h"
class HUD :  public QGraphicsView
{
    Q_OBJECT
private:
    QApplication *window;
    MainMenu *mainmenu;
    GameScene *game;

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
