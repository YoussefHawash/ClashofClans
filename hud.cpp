#include "hud.h"
#include <QAudioOutput>
#include <QBoxLayout>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QLabel>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSizePolicy>

HUD::HUD(QApplication *a)
    : window(a)
{
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    DisplayMainMenu();
}
void HUD::DisplayMainMenu()
{
    QMediaPlayer *sound = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput();
    sound->setLoops(QMediaPlayer::Infinite);
    sound->setSource(QUrl("qrc:/sounds/Resources/Backgroundmusic.mp3"));
    sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(1);
    sound->play();
    mainmenu = new MainMenu(audioOutput);
    connect(mainmenu, SIGNAL(play()), this, SLOT(start()));
    connect(mainmenu, SIGNAL(exit()), this, SLOT(exit()));
    mainmenu->show();
}
void HUD::start()
{
    mainmenu->hide();
    if (mainmenu->fullscreen()) {
        showFullScreen();
    } else {
        setFixedSize(1280, 720);
    }
    game = new GameScene;
    setScene(game);
    game->setSceneRect(0, 0, width(), height());
    show();
}
void HUD::exit()
{
    mainmenu->hide();
    window->quit();
}
HUD::~HUD() {}
