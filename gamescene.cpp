#include "gamescene.h"

GameScene::GameScene(int level, double w, double h)
    : Wavenum(1)
    , gamelevel(level)
    , clickable(true)
{
    QPixmap *bgPixmap = new QPixmap(":/Imgs/Resources/GrassBackgorund.jpg");
    setBackgroundBrush(bgPixmap->scaled(w, h));
    setSceneRect(0, 0, w, h);
    //BlackWindow In case
    EventWindow = new QGraphicsPixmapItem;
    QPixmap *pause = new QPixmap(":/Imgs/Resources/pause.png");
    *pause = pause->scaled(100, 100);
    EventWindow->setPixmap(*pause);
    EventWindow->setPos(1180 / 2, 720 / 2);
    EventWindow->setZValue(10);
    addItem(EventWindow);
    EventWindow->hide();
    // display map
    RenderingMap();
    start();
}
void GameScene::MoveToNextLevel()
{
    // hiding all gameover elements
    NextwaveText->hide();
    NextwaveTextNav->hide();
    gamelevel++;
    Wavenum = 1;
    if (gamelevel > 5) {
        RenderingMap();
        start();
    } else
        Gameover(1);
}
void GameScene::RenderingMap()
{
    map.resize(9);
    yfactor = height() / 9;
    xfactor = width() / 16;
    QFile file(":/maps/Resources/map" + QString::number(gamelevel) + ".txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
    } else {
        QTextStream in(&file);
        int a(0), b(0);
        while (!in.atEnd() && a != 9) {
            int value;
            in >> value;

            map[a].push_back(value);
            b++;
            if (b == 16) {
                b = 0;
                a++;
            }
        }

        for (size_t i = 0; i < map.size(); ++i) {
            for (size_t j = 0; j < map[i].size(); ++j) {
                if (map[i][j] == 1) { // townall =1
                    townhall = new TownHall(this, j * xfactor, i * yfactor, xfactor, yfactor);
                    addItem(townhall);
                } else if (map[i][j] == 3) { // fence = 3
                    //Setting The fence to be rendered
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
                    Fence *fence = new Fence(this, j * xfactor, i * yfactor, xfactor, yfactor, Edges);
                    addItem(fence);

                } else if (map[i][j] == 2) { // defence unit =2
                    Cannon = new DefenseUnit(this, j * xfactor, i * yfactor, xfactor, yfactor, 1);
                    addItem(Cannon);
                }
            }
        }
    }
}


void GameScene::start()
{
    clickable = true;
    if (Wavenum > 1) {
        NextwaveText->hide();
        NextwaveTextNav->hide();
    }

    //setting time
    WaveTime = 60;
    //Wave Time Label
    WaveInfo = new QGraphicsTextItem();
    WaveInfo->setDefaultTextColor(Qt::black);
    WaveInfo->setFont(QFont("serif", 16));
    WaveInfo->setPlainText("Wave " + QString::number(Wavenum));
    WaveInfo->setPos(0, 0);
    addItem(WaveInfo);
    // Wave label
    TimeInfo = new QGraphicsTextItem();
    TimeInfo->setDefaultTextColor(Qt::black);
    TimeInfo->setFont(QFont("serif", 16));
    TimeInfo->setPlainText("Time Remaining : " + QString::number(WaveTime));
    TimeInfo->setPos(0, 25);
    addItem(TimeInfo);
    //Pause Info
    TogglePause = new QGraphicsTextItem();
    TogglePause->setDefaultTextColor(Qt::black);
    TogglePause->setFont(QFont("serif", 16));
    TogglePause->setPlainText("[Escape] To Pause");
    TogglePause->setPos(0, 48);
    addItem(TogglePause);
    //Times

    connect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
    EnemyCreation->start(CreationFrequency);
    Wavetimer = new QTimer();
    connect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    Wavetimer->start(1000);
}
void GameScene::EndWave()
{
    if (WaveTime == 0 && Wavenum == 3) {
        Gameover(1);
    } else if (WaveTime == 0 && Wavenum < 3) {
        //Clearing
        clickable = false;
        clearEnemies();
        //hide HUD
        WaveInfo->hide();
        TimeInfo->hide();
        TogglePause->hide();
        //Disconnect Timers
        QObject::disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
        QObject::disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
        //Displaying
        NextwaveText = new QGraphicsTextItem();
        NextwaveText->setDefaultTextColor(Qt::white);
        NextwaveText->setFont(QFont("serif", 48));
        NextwaveText->setPlainText("Wave one Ended");
        NextwaveText->setPos(width() / 2 - 180, height() / 2 - 48);
        addItem(NextwaveText);
        NextwaveTextNav = new QGraphicsTextItem();
        NextwaveTextNav->setDefaultTextColor(Qt::black);
        NextwaveTextNav->setFont(QFont("serif", 16));
        NextwaveTextNav->setPlainText("[Enter] Next Wave \n[Escape] MainMenu");
        NextwaveTextNav->setPos(width() / 2 - 180, height() / 2 + 48);
        addItem(NextwaveTextNav);
        Wavenum++;
        CreationFrequency = (CreationFrequency * 2) / (3);
    } else {
        WaveTime--;
        TimeInfo->setPlainText("Time Remaining : " + QString::number(WaveTime));
    }
}
void GameScene::Gameover(bool state = 0)
{
    clickable = false;
    disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
    // Clean up any existing items
    clear();
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("serif", 48));
    gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
    if (state) {
        // Display game over text
        gameOverText->setDefaultTextColor(Qt::green);
        gameOverText->setPlainText("Victory!");
        if (gamelevel > 5) {
            NextwaveTextNav->setPlainText("[Enter] Next Level \n[Escape] MainMenu");
            NextwaveTextNav->show();
        }
    } else // Display game over text
        gameOverText->setPlainText("GAME OVER!");
    addItem(gameOverText);
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
    if (clickable && event->button() == Qt::LeftButton) {
        // Get the mouse cursor position
        QPointF mousePos = event->scenePos();
        // Pass the mouse position to the shoot function
        shoot(mousePos);
    }
}
void GameScene::shoot(const QPointF &mousePos)
{
    Bullet *bullet = new Bullet(Cannon->x() + (xfactor / 2),
                                Cannon->y() + (yfactor / 2),
                                mousePos.x(),
                                mousePos.y());
    addItem(bullet);
}
void GameScene::keyPressEvent(QKeyEvent *event)
{
    // Handle key press event
    if (WaveTime != 0 && event->key() == Qt::Key_Escape) {
        TogglePauseFunc();
    } else if (WaveTime == 0 && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        if (Wavenum == 3)
            MoveToNextLevel();
        else
            start();

    } else if (WaveTime == 0 && event->key() == Qt::Key_Escape) {
        ReturnMainMenu();
    }
}
void GameScene::TogglePauseFunc()
{
    if (clickable) {
        TogglePause->setPlainText("[Escape] To Resume");
        EventWindow->show();
        clickable = false;
        EnemyCreation->stop();
        Wavetimer->stop();
        Player::movetime->stop();
    } else {
        TogglePause->setPlainText("[Escape] To Pause");
        EventWindow->hide();
        clickable = true;
        EnemyCreation->start();
        Wavetimer->start();
        Player::movetime->start();
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
        Enemy *enemy = new Enemy(RandPos, 0, townhall->x(), townhall->y(), 20);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    } else if (Edge == 1) {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(width(), RandPos, townhall->x(), townhall->y(), 20);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    } else if (Edge == 2) {
        RandPos = rand() % int(width());
        Enemy *enemy = new Enemy(RandPos, height(), townhall->x(), townhall->y(), 20);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    } else {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(0, RandPos, townhall->x(), townhall->y(), 20);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    }
}
