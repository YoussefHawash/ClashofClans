#include "hud.h"

HUD::HUD(QApplication *a)
    : App(a)
{
    setWindowIcon(QIcon(":/Imgs/Resources/icon.png"));
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    sound = new QMediaPlayer;
    audioOutput = new QAudioOutput();
    sound->setLoops(QMediaPlayer::Infinite);
    sound->setSource(QUrl("qrc:/sounds/Resources/Backgroundmusic.mp3"));
    sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(1);
    sound->play();
    DisplayMainMenu();
}
void HUD::DisplayMainMenu()
{
    mainmenu = new MainMenu(audioOutput);
    connect(mainmenu, SIGNAL(newgame()), this, SLOT(newgame()));
    connect(mainmenu, SIGNAL(randomgame()), this, SLOT(randomgame()));
    connect(mainmenu, SIGNAL(storymode()), this, SLOT(storymode()));
    connect(mainmenu, SIGNAL(exit()), this, SLOT(exit()));
    mainmenu->show();
}
void HUD::exit()
{
    mainmenu->hide();
    App->quit();
}
HUD::~HUD() {}

void HUD::newgame()
{
    sound->setSource(QUrl("qrc:/sounds/Resources/storymode.mp3"));
    sound->play();
    mainmenu->hide();
    if (mainmenu->fullscreen()) {
        showFullScreen();
    } else {
        setFixedSize(1280, 720);
    }
    game = new GameScene(0);
    setScene(game);
    game->setSceneRect(0, 0, width(), height());
    setWindowTitle("New Game");
    show();
}

void HUD::randomgame()
{
    sound->setSource(QUrl("qrc:/sounds/Resources/storymode.mp3"));
    sound->play();
    mainmenu->hide();
    if (mainmenu->fullscreen()) {
        showFullScreen();
    } else {
        setFixedSize(1280, 720);
    }
    game = new GameScene(1);
    setScene(game);
    game->setSceneRect(0, 0, width(), height());
    setWindowTitle("Random Game");
    show();
}

void HUD::storymode()
{
    sound->setSource(QUrl("qrc:/sounds/Resources/storymode.mp3"));
    sound->play();
    mainmenu->hide();
    if (mainmenu->fullscreen()) {
        showFullScreen();
    } else {
        setFixedSize(1280, 720);
    }
    game = new GameScene(2);
    setScene(game);
    game->setSceneRect(0, 0, width(), height());
    setWindowTitle("Story Mode");
    show();
}
