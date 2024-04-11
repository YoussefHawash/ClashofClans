#include "hud.h"
#include <QBoxLayout>
#include <QDebug>
#include <QGraphicsTextItem>

#include <QSizePolicy>
HUD::HUD(QApplication *a)
    : window(a)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    DisplayMainMenu();
}
void HUD::DisplayMainMenu()
{
    mainmenu = new MainMenu();
    connect(mainmenu, SIGNAL(play()), this, SLOT(start()));
    connect(mainmenu, SIGNAL(exit()), this, SLOT(exit()));
    mainmenu->show();
}
void HUD::start()
{
    mainmenu->hide();
    game = new GameScene;
    this->setScene(game);
    if (mainmenu->fullscreen()) {
        this->showFullScreen();
    } else {
        this->setFixedSize(1280, 720);
    }
    game->setSceneRect(0, 0, this->width(), this->height());
    this->show();
}
void HUD::exit()
{
    mainmenu->hide();
    window->quit();
}
HUD::~HUD() {}
