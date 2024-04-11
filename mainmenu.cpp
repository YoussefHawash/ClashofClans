#include "mainmenu.h"
#include <QSignalMapper>
#include <QSize>

MainMenu::MainMenu(QAudioOutput *audioOutput)
    : Output(audioOutput)

{
    this->setWindowIcon(QIcon(":/Imgs/Resources/icon.png"));
    this->setFixedSize(1280, 720);
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
    connect(play_btn, &QPushButton::clicked, this, &MainMenu::play);
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

void MainMenu::ShowMainMenu()
{
    this->setWindowTitle("Main Menu");
    QPixmap bkgnd(":/Imgs/Resources/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
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
    QCheckBox *fullscreen_check = new QCheckBox("Full Screen");
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QLabel *level_label = new QLabel("Level");
    QComboBox *levels = new QComboBox();
    levels->addItem("Level 1");
    levels->addItem("Level 2");
    levels->addItem("Level 3");
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
    connect(mainmenu_btn, &QPushButton::clicked, this, &MainMenu::ShowMainMenu);
    connect(volume, &QSlider::valueChanged, this, &MainMenu::sliderValueChanged);
    connect(levels, QOverload<int>::of(&QComboBox::activated), this, &MainMenu::comboBoxActivated);
}

void MainMenu::ShowSettings()
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
