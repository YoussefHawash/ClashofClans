#include "mainmenu.h"

MainMenu::MainMenu(QAudioOutput *audioOutput)
    : mute(0)
    , volumelevel(100)
    , gamelevel(1)
    , Output(audioOutput)
{
    //Setting The MainWindow
    setWindowIcon(QIcon(":/Imgs/Resources/icon.png"));
    setFixedSize(1280, 720);
    //Setting All UIs
    SetSettingsContainer();
    SetMainMenuContainer();
    SetGamesContainer();
    //Showing MainMenu
    ShowMainMenu();
}

void MainMenu::SetMainMenuContainer()
{
    //Adding All Elements
    mainwindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(mainwindow);
    QLabel *welcome = new QLabel("Welcome");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QPushButton *play_btn = new QPushButton("Play");
    QPushButton *settings_btn = new QPushButton(QString("Settings"));
    QPushButton *exit_btn = new QPushButton(QString("Exit"));

    //Customizitation to all the layers

    //Window

    mainwindow->setGeometry(100, 150, 480, 420);
    mainwindow->setObjectName("mainwindow");
    mainwindow->setStyleSheet("#mainwindow{background: rgba(34,32,40,0.72);border-radius: 20px;}");

    //Main Vertical Layout

    layout->setContentsMargins(50, 0, 50, 0);
    layout->addWidget(welcome, 0, Qt::AlignHCenter);
    layout->addLayout(hLayout1);
    layout->addLayout(hLayout2);
    layout->addLayout(hLayout3);

    //Welcome Label

    QFont font("Arial", 42, QFont::Bold);
    welcome->setStyleSheet("color: gray;");
    welcome->setFont(font);
    welcome->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    //hlayout1

    hLayout1->addStretch();
    hLayout1->addWidget(play_btn);
    hLayout1->addStretch();

    //Playbtn

    play_btn->setFixedSize(250, 50);
    connect(play_btn, &QPushButton::clicked, this, &MainMenu::ShowGames);

    //hlayout2

    hLayout2->addStretch();
    hLayout2->addWidget(settings_btn);
    hLayout2->addStretch();

    //Settingsbtn

    settings_btn->setFixedSize(250, 50);
    connect(settings_btn, &QPushButton::clicked, this, &MainMenu::ShowSettings);

    //hlayout3

    hLayout3->addStretch();
    hLayout3->addWidget(exit_btn);
    hLayout3->addStretch();

    //exitbtn

    exit_btn->setFixedSize(250, 50);
    connect(exit_btn, &QPushButton::clicked, this, &MainMenu::exit);
}

void MainMenu::SetGamesContainer()
{
    //Adding All Elements

    gameswindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(gameswindow);
    QLabel *Games = new QLabel("Games");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QHBoxLayout *hLayout4 = new QHBoxLayout;
    QPushButton *newgame_btn = new QPushButton("New Game");
    QPushButton *mainmenu_btn = new QPushButton(QString("Return to Main Menu"));

    //Customizitation to all the layers

    //Window

    gameswindow->setGeometry(400, 150, 480, 420);
    gameswindow->setObjectName("gameswindow");
    gameswindow->setStyleSheet(
        "#gameswindow{background: rgba(34,32,40,0.72);border-radius: 20px;}");

    //Main Vertical Layout

    layout->setContentsMargins(50, 0, 50, 0);
    layout->addWidget(Games, 0, Qt::AlignHCenter);
    layout->addLayout(hLayout1);
    layout->addLayout(hLayout2);
    layout->addLayout(hLayout3);
    layout->addLayout(hLayout4);

    //Games Label

    QFont font("Arial", 42, QFont::Bold);
    Games->setFont(font);
    Games->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    Games->setStyleSheet("color: gray;");

    //hlayout1

    hLayout1->addStretch();
    hLayout1->addWidget(newgame_btn);
    hLayout1->addStretch();

    //Playbtn

    newgame_btn->setFixedSize(250, 50);
    connect(newgame_btn, &QPushButton::clicked, this, &MainMenu::Emit_NEWGAME);

    //hlayout4

    hLayout4->addStretch();
    hLayout4->addWidget(mainmenu_btn);
    hLayout4->addStretch();

    //mainmenubtn

    mainmenu_btn->setFixedSize(250, 50);
    connect(mainmenu_btn, &QPushButton::clicked, this, &MainMenu::ShowMainMenu);
}

void MainMenu::SetSettingsContainer()
{
    //Adding All Elements
    settingswindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(settingswindow);
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QHBoxLayout *hLayout4 = new QHBoxLayout;
    QLabel *settings = new QLabel("Settings");
    QCheckBox *mute_check = new QCheckBox("Mute");
    QLabel *level_label = new QLabel("Level");
    QComboBox *levels = new QComboBox();
    volume_label = new QLabel("Volume: 100%");
    QSlider *volume = new QSlider(Qt::Horizontal);
    QPushButton *mainmenu_btn = new QPushButton(QString("Return To Main Menu"));

    //Customizitation to all the layers

    //Window

    settingswindow->setGeometry(100, 150, 480, 420);
    settingswindow->setObjectName("settingswindow");
    settingswindow->setStyleSheet(
        "#settingswindow{background: rgba(34,32,40,0.72);border-radius: 20px;}");

    //Main Vertical Layout

    layout->setContentsMargins(50, 0, 50, 0);
    layout->addWidget(settings, 0, Qt::AlignHCenter);
    layout->addLayout(hLayout1);
    layout->addLayout(hLayout2);
    layout->addLayout(hLayout3);
    layout->addLayout(hLayout4);

    //Settings Label

    QFont font("Arial", 42, QFont::Bold);
    settings->setFont(font);
    settings->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    settings->setStyleSheet("color: gray;");

    //hlayout1

    hLayout1->addWidget(mute_check);
    //Mute Checkbox

    connect(mute_check, &QCheckBox::stateChanged, this, &MainMenu::checkBoxStateChanged);

    //hlayout2

    hLayout2->addWidget(level_label);
    hLayout2->addWidget(levels);

    //Levels ComboBox

    levels->addItems({"Peaceful", "Easy", "Normal", "Difficult", "Extreme"});
    connect(levels, QOverload<int>::of(&QComboBox::activated), this, &MainMenu::comboBoxActivated);

    //hlayout3

    hLayout3->addWidget(volume_label);
    hLayout3->addStretch();
    hLayout3->addWidget(volume);

    //volume Slider

    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(100);
    connect(volume, &QSlider::valueChanged, this, &MainMenu::sliderValueChanged);

    //hlayout4

    hLayout4->addStretch();
    hLayout4->addWidget(mainmenu_btn);
    hLayout4->addStretch();

    //MainMenu Button

    mainmenu_btn->setFixedSize(250, 50);
    connect(mainmenu_btn, &QPushButton::clicked, this, &MainMenu::ShowMainMenu);
}

//Showing Methods

void MainMenu::ShowMainMenu()
{
    //Setting Theme

    setWindowTitle("Main Menu");
    QPixmap bkgnd(":/Imgs/Resources/Main.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);

    //Showing

    settingswindow->hide();
    gameswindow->hide();
    mainwindow->show();
}

void MainMenu::ShowGames()
{
    //Setting Theme

    setWindowTitle("Games");
    QPixmap bkgnd(":/Imgs/Resources/Games.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);

    //Showing

    mainwindow->hide();
    gameswindow->show();
}

void MainMenu::ShowSettings()
{
    //Setting Theme

    setWindowTitle("Settings");
    QPixmap bkgnd(":/Imgs/Resources/Settings.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);

    //Showing

    mainwindow->hide();
    settingswindow->show();
}

//Getters
bool MainMenu::IsMute() const
{
    if (mute) {
        return 1;
    } else {
        return 0;
    }
}

//Slots
void MainMenu::checkBoxStateChanged(bool state)
{
    mute = state;
    if(mute)
        Output->setVolume(0);
    else
        Output->setVolume(double(volumelevel)/100);

}
void MainMenu::sliderValueChanged(int value)
{
    volume_label->setText(QString("Volume: %1%").arg(value));
    if(!mute)
     Output->setVolume(double(value) / 100);
    volumelevel = value;
}
void MainMenu::comboBoxActivated(int index)
{
    gamelevel = index + 1;
}

void MainMenu::Emit_NEWGAME() { emit newgame(gamelevel); };
