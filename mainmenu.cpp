#include "mainmenu.h"
#include <QSignalMapper>
#include <QSize>

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Main Menu");
    this->setWindowIcon(QIcon(":/Imgs/Resources/icon.png"));
    this->setFixedSize(1280, 720);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QPixmap bkgnd(":/Imgs/Resources/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    this->SetSettings();
    this->SetMainMenu();
    this->ShowMainMenu();
}

void MainMenu::SetMainMenu()
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
    mainwindow->setGeometry(400, 200, 480, 320);
    mainwindow->setObjectName("window");
    mainwindow->setStyleSheet("#window{background: rgba(0, 39, 70, 0.82);border-radius: 16px;}");
    //Layout
    layout->setContentsMargins(50, 0, 50, 0);
    layout->addWidget(welcome, 0, Qt::AlignHCenter);
    layout->addLayout(hLayout1);
    layout->addLayout(hLayout2);
    layout->addLayout(hLayout3);
    //Welcome Label
    QFont font("Arial", 42, QFont::Bold);
    welcome->setFont(font);
    welcome->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    //hlayout1
    hLayout1->addStretch();
    hLayout1->addWidget(play_btn);
    hLayout1->addStretch();
    //Playbtn
    play_btn->setFixedSize(150, 30);
    connect(play_btn, &QPushButton::clicked, this, &MainMenu::play);
    //hlayout2
    hLayout2->addStretch();
    hLayout2->addWidget(settings_btn);
    hLayout2->addStretch();
    //Settingsbtn
    settings_btn->setFixedSize(150, 30);
    connect(settings_btn, &QPushButton::clicked, this, &MainMenu::ShowSettings);
    //hlayout3
    hLayout3->addStretch();
    hLayout3->addWidget(exit_btn);
    hLayout3->addStretch();
    //exitbtn
    exit_btn->setFixedSize(150, 30);
    connect(exit_btn, &QPushButton::clicked, this, &MainMenu::exit);
}

void MainMenu::ShowMainMenu()
{
    IsFullscreen = fullscreen_check->isChecked();
    volumelevel = volume->value();
    level = levels->currentIndex() + 1;
    settingswindow->hide();
    mainwindow->show();
}

bool MainMenu::fullscreen()
{
    if (IsFullscreen) {
        return 1;
    } else {
        return 0;
    }
}
void MainMenu::SetSettings()
{
    settingswindow = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(settingswindow);
    QLabel *settings = new QLabel("Settings");
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    fullscreen_check = new QCheckBox("Full Screen");
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QLabel *level_label = new QLabel("Level");
    levels = new QComboBox();
    levels->addItem("Level 1");
    levels->addItem("Level 2");
    levels->addItem("Level 3");
    QHBoxLayout *hLayout3 = new QHBoxLayout;
    QLabel *volume_label = new QLabel("Volume");
    volume = new QSlider(Qt::Horizontal);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(100);
    QHBoxLayout *hLayout4 = new QHBoxLayout;
    QPushButton *mainmenu_btn = new QPushButton(QString("Return To Main Menu"));
    //Customizitation to all the layers
    //Window
    settingswindow->setGeometry(400, 200, 480, 320);
    settingswindow->setObjectName("window");
    settingswindow->setStyleSheet(
        "#window{background: rgba(0, 39, 70, 0.82);border-radius: 16px;}");
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
    //hlayout1
    hLayout1->addStretch();
    hLayout1->addWidget(fullscreen_check);
    hLayout1->addStretch();
    //fullscreen_check
    //hlayout2
    hLayout2->addWidget(level_label);
    hLayout2->addWidget(levels);
    //levels
    //hlayout3

    hLayout3->addWidget(volume_label);
    hLayout3->addWidget(volume);
    //volume
    //hlayout4
    hLayout4->addStretch();
    hLayout4->addWidget(mainmenu_btn);
    hLayout4->addStretch();
    mainmenu_btn->setFixedSize(150, 30);
    connect(mainmenu_btn, &QPushButton::clicked, this, &MainMenu::ShowMainMenu);
}

void MainMenu::ShowSettings()
{
    mainwindow->hide();
    settingswindow->show();
}
