#include "mainmenu.h"

MainMenu::MainMenu(QAudioOutput *audioOutput)
    : IsFullscreen(0)
    , volumelevel(100)
    , level(1)
    , Output(audioOutput)
{
    setWindowIcon(QIcon(":/Imgs/Resources/icon.png"));
    setFixedSize(1280, 720);
    SetSettingsWindow();
    SetMainWindow();
    SetGamesWindow();
    ShowMainWindow();
}

void MainMenu::SetMainWindow()
{
    mainwindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(mainwindow);
    QLabel *welcome = new QLabel("Welcome");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QPushButton *play_btn = new QPushButton("Play");
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QPushButton *settings_btn = new QPushButton(QString("Settings"));
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QPushButton *exit_btn = new QPushButton(QString("Exit"));
    //Customizitation to all the layers
    //Window
    mainwindow->setGeometry(100, 150, 480, 420);
    mainwindow->setObjectName("window");
    mainwindow->setStyleSheet("#window{background: rgba(34,32,40,0.72);border-radius: 20px;}");
    //Layout
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
    connect(play_btn, &QPushButton::clicked, this, &MainMenu::ShowGamesWindow);
    //hlayout2
    hLayout2->addStretch();
    hLayout2->addWidget(settings_btn);
    hLayout2->addStretch();
    //Settingsbtn
    settings_btn->setFixedSize(250, 50);
    connect(settings_btn, &QPushButton::clicked, this, &MainMenu::ShowSettingsWindow);
    //hlayout3
    hLayout3->addStretch();
    hLayout3->addWidget(exit_btn);
    hLayout3->addStretch();
    //exitbtn
    exit_btn->setFixedSize(250, 50);
    connect(exit_btn, &QPushButton::clicked, this, &MainMenu::exit);
}

void MainMenu::SetGamesWindow()
{
    gameswindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(gameswindow);
    QLabel *Games = new QLabel("Games");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QPushButton *newgame_btn = new QPushButton("New Game");
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QPushButton *randommap_btn = new QPushButton(QString("Random Map"));
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QPushButton *storymode_btn = new QPushButton(QString("Story Mode"));
    QHBoxLayout *hLayout4 = new QHBoxLayout;
    QPushButton *mainmenu_btn = new QPushButton(QString("Main Menu"));
    //Customizitation to all the layers
    //Window
    gameswindow->setGeometry(400, 150, 480, 420);
    gameswindow->setObjectName("window");
    gameswindow->setStyleSheet("#window{background: rgba(34,32,40,0.72);border-radius: 20px;}");
    //Layout
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
    connect(newgame_btn, &QPushButton::clicked, this, &MainMenu::newgame);
    //hlayout2
    hLayout2->addStretch();
    hLayout2->addWidget(randommap_btn);
    hLayout2->addStretch();
    //Settingsbtn
    randommap_btn->setFixedSize(250, 50);
    connect(randommap_btn, &QPushButton::clicked, this, &MainMenu::randomgame);
    //hlayout3
    hLayout3->addStretch();
    hLayout3->addWidget(storymode_btn);
    hLayout3->addStretch();
    //storymode_btn
    storymode_btn->setFixedSize(250, 50);
    connect(storymode_btn, &QPushButton::clicked, this, &MainMenu::storymode);
    //hlayout4
    hLayout4->addStretch();
    hLayout4->addWidget(mainmenu_btn);
    hLayout4->addStretch();
    //mainmenubtn
    mainmenu_btn->setFixedSize(250, 50);
    connect(mainmenu_btn, &QPushButton::clicked, this, &MainMenu::ShowMainWindow);
}

void MainMenu::SetSettingsWindow()
{
    settingswindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(settingswindow);
    QLabel *settings = new QLabel("Settings");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    QCheckBox *fullscreen_check = new QCheckBox("Full Screen");
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QLabel *level_label = new QLabel("Level");
    QComboBox *levels = new QComboBox();
    levels->addItem("Peacful");
    levels->addItem("Easy");
    levels->addItem("Normal");
    levels->addItem("Difficult");
    levels->addItem("Extreme");
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    volume_label = new QLabel("Volume: 100%");
    QSlider *volume = new QSlider(Qt::Horizontal);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(100);
    QHBoxLayout *hLayout4 = new QHBoxLayout;
    QPushButton *mainmenu_btn = new QPushButton(QString("Return To Main Menu"));
    //Customizitation to all the layers
    //Window
    settingswindow->setGeometry(100, 150, 480, 420);
    settingswindow->setObjectName("window");
    settingswindow->setStyleSheet("#window{background: rgba(34,32,40,0.72);border-radius: 20px;}");
    //Layout
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

    hLayout1->addWidget(fullscreen_check);

    //fullscreen_check
    //hlayout2
    hLayout2->addWidget(level_label);
    hLayout2->addWidget(levels);
    //levels
    //hlayout3

    hLayout3->addWidget(volume_label);
    hLayout3->addStretch();
    hLayout3->addWidget(volume);
    //volume
    //hlayout4
    hLayout4->addStretch();
    hLayout4->addWidget(mainmenu_btn);
    hLayout4->addStretch();
    mainmenu_btn->setFixedSize(250, 50);
    connect(fullscreen_check, &QCheckBox::stateChanged, this, &MainMenu::checkBoxStateChanged);
    connect(mainmenu_btn, &QPushButton::clicked, this, &MainMenu::ShowMainWindow);
    connect(volume, &QSlider::valueChanged, this, &MainMenu::sliderValueChanged);
    connect(levels, QOverload<int>::of(&QComboBox::activated), this, &MainMenu::comboBoxActivated);
}

void MainMenu::ShowMainWindow()
{
    this->setWindowTitle("Main Menu");
    QPixmap bkgnd(":/Imgs/Resources/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    settingswindow->hide();
    gameswindow->hide();
    mainwindow->show();
}

void MainMenu::ShowGamesWindow()
{
    this->setWindowTitle("Games");
    QPixmap bkgnd(":/Imgs/Resources/games.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    mainwindow->hide();
    gameswindow->show();
}

void MainMenu::ShowSettingsWindow()
{
    this->setWindowTitle("Settings");
    QPixmap bkgnd(":/Imgs/Resources/settings.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    mainwindow->hide();
    settingswindow->show();
}

bool MainMenu::fullscreen()
{
    if (IsFullscreen) {
        return 1;
    } else {
        return 0;
    }
}

void MainMenu::checkBoxStateChanged(bool state)
{
    IsFullscreen = state;
}
void MainMenu::sliderValueChanged(int value)
{
    volume_label->setText(QString("Volume: %1%").arg(value));
    Output->setVolume(double(value) / 100);
    volumelevel = value;
}
void MainMenu::comboBoxActivated(int index)
{
    level = index + 1;
}
