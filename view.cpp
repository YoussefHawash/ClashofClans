#include "view.h"
 GameScene *gamescene;
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
    DisplayGameMenu();
}

void View::DisplayGameMenu()
{
    MainUI = new MainMenu(audioOutput);
    MainUI->show();
    connect(MainUI, &MainMenu::newgame, this, &View::NewGame);
    connect(MainUI, SIGNAL(exit()), this, SLOT(Exit()));
}

void View::NewGame(int level)
{
    if (MainUI->IsFullscreen())
        showFullScreen();
    else
        setFixedSize(1280, 720);

    gamescene = new GameScene(level, width(), height());
    setWindowTitle("New Game");
    setScene(gamescene);
    MainUI->hide();
    show();
    connect(gamescene, SIGNAL(ReturnMainMenu()), this, SLOT(ReturnToMainMenu()));
}

void View::ReturnToMainMenu()
{
    hide();
    delete gamescene;
    MainUI->show();
}

void View::Exit()
{
    MainUI->hide();
    App->quit();
}
