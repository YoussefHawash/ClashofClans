#include "gamescene.h"
#include <QFile>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "GameElements/bullet.h"
#include "GameElements/defenseunit.h"
#include "GameElements/enemy.h"
#include "GameElements/fence.h"
#include "GameElements/townworkers.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
GameScene::GameScene(double w, double h)

{
    QPixmap bgPixmap(":/Imgs/Resources/GrassBackgorund.jpg");
    setBackgroundBrush(bgPixmap.scaled(w, h));
    setSceneRect(0, 0, w, h);
    // MAP RENDERING
    int game_rows = 9;
    int game_cols = 16;
    map.resize(game_rows);


    QFile file(":/Imgs/map.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
        return;
    }

    QTextStream stream(&file);
    QString temp = stream.readAll();
    qDebug() << temp;


    QStringList lines = temp.split("\n", Qt::SkipEmptyParts);


    map.clear();
    for (const QString& line : lines) {
        QStringList tokens = line.split(' ', Qt::SkipEmptyParts);
        std::vector<int> row; // Use std::vector<int> instead of QVector<int>
        for (const QString& token : tokens) {
            bool ok;
            int value = token.toInt(&ok);
            if (!ok) {
                qDebug() << "Failed to convert token to integer:" << token;

            }
            row.push_back(value);
        }
        map.push_back(row);
    }

    file.close();


    // for (int var = 0; var < map.size(); ++var) {
    //     map[var].resize(game_cols);
    // }
    // for (int i = 0; i < map.size(); i++) {
    //     for (int j = 0; j < map[i].size(); j++) {
    //         map[i][j] = 0;
    //     }
    // }
    // map[4][7] = 1;
    // map[3][7] = 2;
    // // adding elements
    // for (int var = 2; var < 7; ++var) {
    //     map[var][5] = 3;
    //     map[var][9] = 3;
    // }
    // for (int var = 5; var < 10; ++var) {
    //     map[2][var] = 3;
    //     map[6][var] = 3;
    // }



    // display map
    RenderingMap();
    clickable = true;
    start();
}


void GameScene::RenderingMap()
{
    yfactor = height() / map.size();
    xfactor = width() / map[0].size();

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 1) { // townall =1
                townhall = new TownHall(xfactor, yfactor);
                x_townhall = j * xfactor;
                y_townhall = i * yfactor;
                townhall->setPos(x_townhall, y_townhall);
                townhall->SetHealth(this, 5000);
                addItem(townhall);
            } else if (map[i][j] == 3) { // fence = 3
                vector<int> Edges;
                if (map[i - 1][j] == 3) {
                    Edges.push_back(0);
                }
                if (map[i + 1][j] == 3) {
                    Edges.push_back(2);
                }
                if (map[i][j - 1] == 3) {
                    Edges.push_back(3);
                }
                if (map[i][j + 1] == 3) {
                    Edges.push_back(1);
                }
                Fence *fence = new Fence(xfactor, yfactor, Edges);
                fence->setPos(j * xfactor, i * yfactor);
                fence->SetHealth(this, 4000);
                addItem(fence);
            } else if (map[i][j] == 2) { // defence unit =2

                DefenseUnit *a = new DefenseUnit(xfactor, yfactor, 1);
                x_cannon = j * xfactor;
                y_cannon = i * yfactor;
                a->setPos(x_cannon, y_cannon);
                addItem(a);
            }
        }
    }
    // Random Workers Generation
    townworkers *workers[2];
    for (int i = 0; i < 2; i++) {
        workers[i] = new townworkers((x_townhall-80)+(i*200),y_townhall);
        addItem(workers[i]);
    }
}

void GameScene::createenemy()
{
    int RandPos;
    srand(time(0));
    // random generator of the enemies
    int Edge = rand() % 4;

    if (Edge == 0) {
        RandPos = rand() % int(width());
        Enemy *enemy = new Enemy(RandPos, 0, x_townhall, y_townhall, 100);
        addItem(enemy);
    } else if (Edge == 1) {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(width(), RandPos, x_townhall, y_townhall, 100);
        addItem(enemy);

    } else if (Edge == 2) {
        RandPos = rand() % int(width());
        Enemy *enemy = new Enemy(RandPos, height(), x_townhall, y_townhall, 100);
        addItem(enemy);

    } else if (Edge == 3) {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(0, RandPos, x_townhall, y_townhall, 100);
        addItem(enemy);
    }
}
void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Get the mouse cursor position
        QPointF mousePos = event->scenePos();
        // Pass the mouse position to the shoot function
        shoot(mousePos);
    }
}
void GameScene::shoot(const QPointF &mousePos)
{
    if (clickable) {
        Bullet *a = new Bullet(x_cannon + (xfactor / 2),
                               y_cannon + (yfactor / 2),
                               mousePos.x(),
                               mousePos.y());
        addItem(a);
    }
}

void GameScene::start()
{
    //setting time
    timeleft = 60;
    // Wave label
    WaveTime = new QGraphicsTextItem();
    WaveTime->setDefaultTextColor(Qt::black);
    WaveTime->setFont(QFont("serif", 16));
    WaveTime->setPlainText("Time Remaining : " + QString::number(timeleft));
    WaveTime->setPos(0, 25);
    addItem(WaveTime);
    //Wave Time Label
    QGraphicsTextItem *WaveLabel = new QGraphicsTextItem();
    WaveLabel->setDefaultTextColor(Qt::black);
    WaveLabel->setFont(QFont("serif", 16));
    WaveLabel->setPlainText("Wave 1");
    WaveLabel->setPos(0, 0);
    addItem(WaveLabel);
    //Times
    EnemyCreation = new QTimer();
    QObject::connect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createenemy()));
    EnemyCreation->start(4000);

    QTimer *Wavetimer = new QTimer();
    QObject::connect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    Wavetimer->start(1000);
}


void GameScene::Gameover()
{
    clickable = 0;
    QObject::disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    QObject::disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createenemy()));

    // Clean up any existing items
    clear();

    QMediaPlayer *sound = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    sound->setSource(QUrl("qrc:/sounds/Resources/Voicy_Barbarian death cry - Clash of Clans.mp3"));
    sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
    sound->play();

    // Display game over text
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("serif", 48));
    gameOverText->setPlainText("GAME OVER!");
    gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
    addItem(gameOverText);

    QPushButton *Return = new QPushButton("Return To mainmenu");
    Return->setFixedSize(400, 120);
    QGraphicsProxyWidget *Return_to_MainMenu = new QGraphicsProxyWidget();
    Return_to_MainMenu->setWidget(Return);
    addItem(Return_to_MainMenu);
    Return_to_MainMenu->setPos(400, 450);
    connect(Return, &QPushButton::clicked,this, &GameScene::Return_to_Menu);

    // delete allocated resources
    delete sound;
    delete audioOutput;

}

void GameScene::EndWave()
{
    if(townhall->gethealth() <=0 ){
        Gameover();
    }
    else if (timeleft == 0) {
        clickable = 0;
        QObject::disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
        QObject::disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createenemy()));
        clear();
        // QMediaPlayer *sound = new QMediaPlayer();
        // QAudioOutput *audioOutput = new QAudioOutput();
        // sound->setSource(QUrl("qrc:/sounds/Resources/Voicy_Barbarian death cry - Clash of Clans.mp3"));
        // sound->setAudioOutput(audioOutput);
        // audioOutput->setVolume(50);
        // sound->play();
        QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
        gameOverText->setDefaultTextColor(Qt::white);
        gameOverText->setFont(QFont("serif", 48));
        gameOverText->setPlainText("Victory!");
        gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
        addItem(gameOverText);



        QPushButton *Return = new QPushButton("Return To mainmenu");
        Return->setFixedSize(400, 120);
        QGraphicsProxyWidget *Return_to_MainMenu = new QGraphicsProxyWidget();
        Return_to_MainMenu->setWidget(Return);
        addItem(Return_to_MainMenu);
        Return_to_MainMenu->setPos(400, 450);
        connect(Return, &QPushButton::clicked,this, &GameScene::Return_to_Menu);
    }
    else {
        timeleft--;
        WaveTime->setPlainText("Time Remaining : " + QString::number(timeleft));
    }
}

void GameScene::Return_to_Menu(){
    qDebug() << "gg";
    //MainMenu* Main_Menu = new MainMenu;
}


