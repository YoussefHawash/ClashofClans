#include "view.h"

View::View(QApplication *a)
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

void View::DisplayMainMenu()
{
    MainUI = new MainMenu(audioOutput);
    connect(MainUI, SIGNAL(newgame()), this, SLOT(NewGame()));
    connect(MainUI, SIGNAL(randomgame()), this, SLOT(RandomGame()));
    connect(MainUI, SIGNAL(storymode()), this, SLOT(StoryMode()));
    connect(MainUI, SIGNAL(exit()), this, SLOT(Exit()));
    MainUI->show();
}

void View::NewGame()
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(width(), height());
    setWindowTitle("New Game");
    setScene(gamescene);
    MainUI->hide();
    show();
}

void View::RandomGame()
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(width(), height());
    setWindowTitle("Random Game");
    setScene(gamescene);

    show();
}

void View::StoryMode()
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(width(), height());
    setWindowTitle("Story Mode");
    setScene(gamescene);
    MainUI->hide();
    show();
}

void View::Exit()
{
    MainUI->hide();
    App->quit();
}

View::~View() {}
