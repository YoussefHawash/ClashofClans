#include "gamescene.h"

GameScene::GameScene(double w, double h)
    : Wavenum(1)
    , clickable(true)
{
    bgPixmap = new QPixmap(":/Imgs/Resources/GrassBackgorund.jpg");
    setBackgroundBrush(bgPixmap->scaled(w, h));
    setSceneRect(0, 0, w, h);
    // display map

    RenderingMap();
    start();
    blackwindow = new QGraphicsRectItem(0, 0, 0, 0);
    QBrush b(Qt::black); // Blue color
    blackwindow->setBrush(b);
    blackwindow->setZValue(10);
    addItem(blackwindow);
}

void GameScene::RenderingMap()
{
    Pause = new QPushButton("Pause");
    Pause->setFixedSize(150, 50);
    PauseWidget = new QGraphicsProxyWidget();
    PauseWidget->setWidget(Pause);
    PauseWidget->setZValue(100);
    addItem(PauseWidget);
    PauseWidget->setPos(1130, 0);
    connect(Pause, &QPushButton::clicked, this, &GameScene::PauseWave);

    map.resize(9);
    yfactor = height() / 9;
    xfactor = width() / 16;
    QFile file(":/maps/Resources/map.txt");
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

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (map[i][j] == 1) { // townall =1
                    townhall = new TownHall(this, j * xfactor, i * yfactor, xfactor, yfactor);
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
                    Player p(0, 0, 0, 0);
                    p.startmove();
                    Fence *fence = new Fence(this, j * xfactor, i * yfactor, xfactor, yfactor, Edges);
                    addItem(fence);

                } else if (map[i][j] == 2) { // defence unit =2
                    x_cannon = j * xfactor;
                    y_cannon = i * yfactor;
                    DefenseUnit *a = new DefenseUnit(this, x_cannon, y_cannon, xfactor, yfactor, 1);
                    addItem(a);
                }
            }
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

void GameScene::start()
{
    clickable = true;
    if (Wavenum > 1) {
        NextWaveButton->hide();
        NextwaveText->hide();
        EndWaveWidget->hide();
    }

    //setting time
    WaveTime = 1;
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

void GameScene::Gameover(bool state = 0)
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
        Gameover(1);
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
    if (clickable && event->button() == Qt::LeftButton) {
        // Get the mouse cursor position
        QPointF mousePos = event->scenePos();
        // Pass the mouse position to the shoot function
        shoot(mousePos);
    }
}
void GameScene::shoot(const QPointF &mousePos)
{
    Bullet *a = new Bullet(x_cannon + (xfactor / 2),
                           y_cannon + (yfactor / 2),
                           mousePos.x(),
                           mousePos.y());
    addItem(a);
}
void GameScene::PauseWave()
{
    if (clickable) {
        blackwindow->setRect(1280 / 4, 720 / 4, 1280 / 2, 720 / 2);
        Pause->setText("Resume");
        PauseWidget->setPos(565, 335);
        clickable = 0;
        EnemyCreation->stop();
        Wavetimer->stop();
        Player::movetime->stop();
    } else {
        blackwindow->setRect(0, 0, 0, 0);
        Pause->setText("Pause");
        PauseWidget->setPos(1130, 0);
        clickable = 1;
        EnemyCreation->start();
        Wavetimer->start();
        Player::movetime->start();
    }
}
