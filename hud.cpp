#include "hud.h"

HUD::HUD(QApplication *a)
    : App(a)
{
    //Setting View
    setWindowIcon(QIcon(":/Imgs/Resources/icon.png"));
    setFixedSize(800, 600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //Setting Sounds
    Sound = new QMediaPlayer;
    audioOutput = new QAudioOutput();
    Sound->setLoops(QMediaPlayer::Infinite);
    Sound->setSource(QUrl("qrc:/sounds/Resources/backgroundmusic.mp3"));
    Sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(1);
    Sound->play();
    //DisplayingMain
    DisplayMainMenu();
}

void HUD::DisplayMainMenu()
{
    MainUI = new MainMenu(audioOutput);
    connect(MainUI, SIGNAL(newgame()), this, SLOT(NewGame()));
    connect(MainUI, SIGNAL(randomgame()), this, SLOT(RandomGame()));
    connect(MainUI, SIGNAL(storymode()), this, SLOT(StoryMode()));
    connect(MainUI, SIGNAL(exit()), this, SLOT(Exit()));
    MainUI->show();
}

void HUD::NewGame()
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(width(), height(), 0);
    setWindowTitle("New Game");
    setScene(gamescene);
    MainUI->hide();
    show();
}

void HUD::RandomGame()
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(width(), height(), 1);
    setWindowTitle("Random Game");
    setScene(gamescene);

    show();
}

void HUD::StoryMode()
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(width(), height(), 2);
    setWindowTitle("Story Mode");
    setScene(gamescene);
    MainUI->hide();
    show();
}

void HUD::Exit()
{
    MainUI->hide();
    App->quit();
}

HUD::~HUD() {}
