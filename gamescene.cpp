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
GameScene::GameScene(double w, double h)
    : Wavenum(1)
    , clickable(true)
{
    QPixmap bgPixmap(":/Imgs/Resources/GrassBackgorund.jpg");
    setBackgroundBrush(bgPixmap.scaled(w, h));
    setSceneRect(0, 0, w, h);
    // display map
    RenderingMap();
    start();
}

void GameScene::RenderingMap()
{
    map.resize(9);
    for (int var = 0; var < 9; ++var) {
        map[var].resize(16, nullptr);
    }
    yfactor = height() / 9;
    xfactor = width() / 16;
    QFile file(":/maps/Resources/map.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
    } else {
        QTextStream in(&file);
        int i(0), j(0);
        while (!in.atEnd()) {
            // Read a single character
            int value;
            in >> value;
            if (value == 1) { // townall =1
                townhall = new TownHall(xfactor, yfactor);
                townhall->setPos(j * xfactor, i * yfactor);
                townhall->SetHealth(this, 5000);
                addItem(townhall);

                map[i][j] = townhall;
            } else if (value == 3) { // fence = 3
                vector<int> Edges;
                // if (map[i - 1][j] != nullptr && typeid(*(map[i - 1][j])) == typeid(Fence)) {
                //     Edges.push_back(0);
                // }
                // if (map[i + 1][j] != nullptr && typeid(*(map[i + 1][j])) == typeid(Fence)) {
                //     Edges.push_back(2);
                // }
                // if (map[i][j - 1] != nullptr && typeid(*(map[i][j - 1])) == typeid(Fence)) {
                //     Edges.push_back(3);
                // }
                // if (map[i][j + 1] != nullptr && typeid(*(map[i][j + 1])) == typeid(Fence)) {
                //     Edges.push_back(1);
                // }
                Player p(0,0,0,0);
                p.startmove();
                Fence *fence = new Fence(xfactor, yfactor, Edges);
                fence->setPos(j * xfactor, i * yfactor);
                fence->SetHealth(this, 4000);
                addItem(fence);
                map[i][j] = fence;
            } else if (value == 2) { // defence unit =2
                DefenseUnit *a = new DefenseUnit(xfactor, yfactor, 1);
                x_cannon = j * xfactor;
                y_cannon = i * yfactor;
                a->setPos(x_cannon, y_cannon);
                addItem(a);
                map[i][j] = a;
            }
            j++;
            if (j == 16) {
                j = 0;
                i++;
            }
        }

        // Random Workers Generation
        townworkers *workers[2];
        for (int i = 0; i < 2; i++) {
            workers[i] = new townworkers((townhall->x() - 80) + (i * 200), townhall->y());
            addItem(workers[i]);
        }
    }
}

void GameScene::createEnemy()
{
    int RandPos;
    srand(time(0));
    // random generator of the enemies
    int Edge = rand() % 4;

    if (Edge == 0) {
        RandPos = rand() % int(width());
        Enemy *enemy = new Enemy(RandPos, 0, townhall->x(), townhall->y(), 100);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::GameEnd);
    } else if (Edge == 1) {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(width(), RandPos, townhall->x(), townhall->y(), 100);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::GameEnd);
    } else if (Edge == 2) {
        RandPos = rand() % int(width());
        Enemy *enemy = new Enemy(RandPos, height(), townhall->x(), townhall->y(), 100);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::GameEnd);
    } else {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(0, RandPos, townhall->x(), townhall->y(), 100);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::GameEnd);
    }
}

void GameScene::start()
{
    clickable = true;
    if (Wavenum > 1) {
        NextWaveButton->hide();
        NextwaveText->hide();
        EndWaveWidget->hide();
    }

    //setting time
    WaveTime = 900;
    // Wave label
    TimeInfo = new QGraphicsTextItem();
    TimeInfo->setDefaultTextColor(Qt::black);
    TimeInfo->setFont(QFont("serif", 16));
    TimeInfo->setPlainText("Time Remaining : " + QString::number(WaveTime));
    TimeInfo->setPos(0, 25);
    addItem(TimeInfo);
    //Wave Time Label
    WaveInfo = new QGraphicsTextItem();
    WaveInfo->setDefaultTextColor(Qt::black);
    WaveInfo->setFont(QFont("serif", 16));
    WaveInfo->setPlainText("Wave " + QString::number(Wavenum));
    WaveInfo->setPos(0, 0);
    addItem(WaveInfo);

    //Times
    EnemyCreation->start(CreationFrequency);
    QObject::connect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));

    Wavetimer = new QTimer();
    QObject::connect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    Wavetimer->start(1000);
}

void GameScene::GameEnd(bool state = 0)
{
    clickable = 0;
    QObject::disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    QObject::disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));

    // Clean up any existing items
    clear();
    if (state) {
        // Display game over text
        QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setFont(QFont("serif", 48));
        gameOverText->setPlainText("GAME OVER!");
        gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
        addItem(gameOverText);
    } else {
        // Display game over text
        QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setFont(QFont("serif", 48));
        gameOverText->setPlainText("Victory!");
        gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
        addItem(gameOverText);
    }
    QPushButton *ReturnButton = new QPushButton("Return To mainmenu");
    ReturnButton->setFixedSize(400, 120);
    QGraphicsProxyWidget *Return_to_MainMenu = new QGraphicsProxyWidget();
    Return_to_MainMenu->setWidget(ReturnButton);
    addItem(Return_to_MainMenu);
    Return_to_MainMenu->setPos(400, 450);
    connect(ReturnButton, &QPushButton::clicked, this, &GameScene::ReturnMainMenu);
}

void GameScene::EndWave()
{
    if (WaveTime == 0 && Wavenum == 3) {
        GameEnd(1);
    } else if (WaveTime == 0 && Wavenum < 3) {
        //Clearing
        clickable = 0;
        clearEnemies();
        WaveInfo->hide();
        TimeInfo->hide();
        QObject::disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
        QObject::disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
        //Displaying
        NextwaveText = new QGraphicsTextItem();
        NextwaveText->setDefaultTextColor(Qt::white);
        NextwaveText->setFont(QFont("serif", 48));
        NextwaveText->setPlainText("Wave one Ended");
        NextwaveText->setPos(width() / 2 - 180, height() / 2 - 48);
        addItem(NextwaveText);
        NextWaveButton = new QPushButton("Move to Next Wave");
        NextWaveButton->setFixedSize(400, 120);
        EndWaveWidget = new QGraphicsProxyWidget();
        EndWaveWidget->setWidget(NextWaveButton);
        addItem(EndWaveWidget);
        EndWaveWidget->setPos(400, 450);
        Wavenum++;
        CreationFrequency = (CreationFrequency * 2) / (3);
        connect(NextWaveButton, &QPushButton::clicked, this, &GameScene::start);
    } else {
        WaveTime--;
        TimeInfo->setPlainText("Time Remaining : " + QString::number(WaveTime));
    }
}

void GameScene::clearEnemies()
{
    for (int i = items().size() - 1; i >= 0; --i) {
        if (Enemy *enemy = dynamic_cast<Enemy *>(items().at(i))) {
            delete enemy;
        }
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
