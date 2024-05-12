#include "gamescene.h"

GameScene::GameScene(int level, double w, double h)
    : Wavenum(1)
    , gamelevel(level)
    , clickable(true)
{
    Enemy::HitTimer->start(1000);
    QPixmap *bgPixmap = new QPixmap(":/Imgs/Resources/GrassBackgorund.jpg");
    setBackgroundBrush(bgPixmap->scaled(w, h));
    setSceneRect(0, 0, w, h);
    //BlackWindow In case
    BoostInfo = new QGraphicsTextItem();
    WaveInfo = new QGraphicsTextItem();
    TimeInfo = new QGraphicsTextItem();
    TogglePause = new QGraphicsTextItem();
    EventWindow = new QGraphicsPixmapItem;
    NextwaveText = new QGraphicsTextItem;
    NextwaveTextNav = new QGraphicsTextItem;
    QPixmap *pause = new QPixmap(":/Imgs/Resources/pause.png");
    *pause = pause->scaled(100, 100);
    EventWindow->setPixmap(*pause);
    EventWindow->setPos(1180 / 2, 720 / 2);
    EventWindow->setZValue(10);
    addItem(EventWindow);
    EventWindow->hide();

    WaveInfo->setDefaultTextColor(Qt::black);
    WaveInfo->setFont(QFont("serif", 16));
    WaveInfo->setPos(0, 0);
    addItem(WaveInfo);
    // Wave label
    TimeInfo->setDefaultTextColor(Qt::black);
    TimeInfo->setFont(QFont("serif", 16));
    TimeInfo->setPos(0, 25);
    addItem(TimeInfo);
    //Pause Info
    TogglePause->setDefaultTextColor(Qt::black);
    TogglePause->setFont(QFont("serif", 16));
    TogglePause->setPos(0, 48);
    addItem(TogglePause);


    CreationFrequency = 10000/(gamelevel+1);


    NextwaveTextNav->setDefaultTextColor(Qt::black);
    NextwaveTextNav->setFont(QFont("serif", 16));
    NextwaveTextNav->setPos(width() / 2 - 180, height() / 2 + 48);
    addItem(NextwaveTextNav);

    // display map
    RenderingMap();
    start();
}
void GameScene::MoveToNextLevel()
{
    // hiding all gameover elements
    gameOverText->hide();
    Navigation->hide();
    gamelevel++;
    Wavenum = 1;
    CreationFrequency = 10000/(gamelevel+1);
    if (gamelevel < 5) {
        RenderingMap();
        start();
    } else
        Gameover(1);
}
void GameScene::RenderingMap()
{
    map.clear();
    map.resize(9);

    yfactor = height() / 9;
    xfactor = width() / 16;
    QFile file(":/maps/Resources/map" + QString::number(gamelevel) + ".txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for reading:" << file.errorString();
    } else {
        QTextStream in(&file);
        int a(0), b(0);
        int townx,towny;
        while (!in.atEnd() && a != 9) {
            int value;
            in >> value;
            Node *n=new Node(a,b,0,0);
            if(value==0){
                n->weight= 1;
                n->type=0;}
            else if (value ==3){
                n->weight=40;
                n->type=3;}
            else if (value ==1){
                n->weight=100;
                n->type=1;
                townx=a;
                towny=b;}
            else{
                n->weight=1000;
                n->type=2;}

            map[a].push_back(n);
            b++;
            if (b == 16) {
                b = 0;
                a++;
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 16; ++j)
            {
                map[i][j]->weight+=sqrt(pow(townx-i,2)+pow(towny-j,2));
            }
        }


        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (map[i][j]->type == 1) { // townall =1
                    townhall = new TownHall(this, j * xfactor, i * yfactor );
                    addItem(townhall);
                } else if (map[i][j]->type == 3) { // fence = 3
                    //Setting The fence to be rendered
                    vector<int> Edges;
                    if (map[i - 1][j]->type == 3) {
                        Edges.push_back(0);
                    }
                    if (map[i + 1][j]->type ==3) {
                        Edges.push_back(2);
                    }
                    if (map[i][j - 1]->type ==3) {
                        Edges.push_back(3);
                    }
                    if (map[i][j + 1]->type == 3) {
                        Edges.push_back(1);
                    }
                    Fence *fence = new Fence(this, j * xfactor, i * yfactor, Edges);
                    addItem(fence);

                } else if (map[i][j]->type == 2) { // defence unit =2
                    Cannon = new DefenseUnit(this, j * xfactor, i * yfactor, gamelevel);
                    addItem(Cannon);
                }
            }
        }
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 16; ++j)
        {
            qDebug()  << map[i][j]->weight;
        }
    }


}

void GameScene::createBooster()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribX(0.0, width());
    std::uniform_real_distribution<double> distribY(0.0, height());

    double x = distribX(gen);
    double y = distribY(gen);

    Booster* boost = new Booster(x, y);
    qDebug() << x;
    qDebug() << y;
    addItem(boost);
}
void GameScene::BoostTimer()
{
    // Wave label

    if(BoostTime>0)
    {
        BoostInfo->setPlainText("Time Remaining : " + QString::number(BoostTime));
        BoostTime--;
    }else if(BoostTime==0)
    {
        BoostInfo->hide();
        QObject::disconnect(BoosterTimer, SIGNAL(timeout()), this, SLOT(createBooster()));
    }



}
void GameScene::ActivateBooster()
{

    if(BoostTime==0)
    {
    BoostTime=10;
    QObject::connect(Wavetimer, SIGNAL(timeout()), this, SLOT(BoostTimer()));
    BoostInfo = new QGraphicsTextItem();
    BoostInfo->setDefaultTextColor(Qt::black);
    BoostInfo->setFont(QFont("serif", 16));
    BoostInfo->setPlainText("Time Remaining : " + QString::number(BoostTime));
    BoostInfo->setPos(0, 75);
    addItem(BoostInfo);
    }
}

void GameScene::start()
{
    Player::movetime->start();
    clickable = true;
    if (Wavenum > 1) {
        NextwaveText->hide();
        NextwaveTextNav->hide();
    }
    //setting time
    WaveTime = 60;
    //Wave Time Label
    TogglePause->setPlainText("[Escape] To Pause");
    TimeInfo->setPlainText("Time Remaining : " + QString::number(WaveTime));
    WaveInfo->setPlainText("Wave " + QString::number(Wavenum));

    WaveInfo->show();
    TimeInfo->show();
    TogglePause->show();

    EnemyCreation->start(CreationFrequency);

    connect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
    Wavetimer = new QTimer();
    connect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    Wavetimer->start(1000);
    BoosterTimer = new QTimer();
    connect(BoosterTimer, SIGNAL(timeout()), this, SLOT(createBooster()));
    BoosterTimer->start(20000);
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
        QObject::disconnect(BoosterTimer, SIGNAL(timeout()), this, SLOT(createBooster()));
        //Displaying

        NextwaveText->setDefaultTextColor(Qt::white);
        NextwaveText->setFont(QFont("serif", 48));
        NextwaveText->setPlainText("Wave "+ QString::number(Wavenum)+ " Ended");
        NextwaveText->setPos(width() / 2 - 180, height() / 2 - 48);
        addItem(NextwaveText);
        NextwaveTextNav->setPlainText("[Enter] Next Wave \n[Escape] MainMenu");
        NextwaveTextNav->show();
        CreationFrequency = (CreationFrequency * 4) / (5);
    } else {
        WaveTime--;
        TimeInfo->setPlainText("Time Remaining : " + QString::number(WaveTime));
    }
}
void GameScene::Gameover(bool state = 0)
{
    WaveTime = 0;
    clickable = false;
    disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
    disconnect(BoosterTimer, SIGNAL(timeout()), this, SLOT(createBooster()));
    // Clean up any existing items
    clearEnemies();
    for (int i = items().size() - 1; i >= 0; --i) {
        if (Building *building = dynamic_cast<Building *>(items().at(i))) {
            delete building;
        }
    }


    gameOverText = new QGraphicsTextItem();
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("serif", 48));
    gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);

    if (state) {
        // Display game over text
        gameOverText->setDefaultTextColor(Qt::green);
        gameOverText->setPlainText("Victory!");
        if (gamelevel < 5) {
            Navigation = new QGraphicsTextItem();
            Navigation->setDefaultTextColor(Qt::black);
            Navigation->setFont(QFont("serif", 16));
            Navigation->setPlainText("[Escape] MainMenu /n[Enter] Next level");

            Navigation->setPos(width() / 2 - 180, height() / 2 + 48);
            Navigation->show();
            addItem(Navigation);
        }
    } else {// Display game over text
        Wavenum=0;

        qDebug() << 1;
        gameOverText->setPlainText("GAME OVER!");
        qDebug() << 1;
        Navigation = new QGraphicsTextItem();
        Navigation->setDefaultTextColor(Qt::black);
        Navigation->setFont(QFont("serif", 16));
        Navigation->setPlainText("[Escape] MainMenu");

        Navigation->setPos(width() / 2 - 180, height() / 2 + 48);
        Navigation->show();
        addItem(Navigation);
    }
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


    if (clickable) {
        if(BoostTime!=0)
        {
            boost=1;
        }
        else{boost=0;}

        Bullet *a = new Bullet(Cannon->x() + (xfactor / 2),
                               Cannon->y() + (yfactor / 2),
                               mousePos.x(),
                               mousePos.y(),boost);
        addItem(a);
        QObject::connect(a, SIGNAL(BoosterActivate()), this, SLOT(ActivateBooster()));
    }

}
void GameScene::keyPressEvent(QKeyEvent *event)
{
    // Handle key press event
    if (WaveTime != 0 && event->key() == Qt::Key_Escape) {
        TogglePauseFunc();
    } else if (WaveTime == 0 && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        if (Wavenum < 3){
            Wavenum++;
            start();}
        else
            MoveToNextLevel();


    } else if (WaveTime == 0 && event->key() == Qt::Key_Escape) {
        emit ReturnMainMenu();
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
        BoosterTimer->stop();
        Player::movetime->stop();
        Enemy::HitTimer->stop();
    } else {
        TogglePause->setPlainText("[Escape] To Pause");
        EventWindow->hide();
        clickable = true;
        EnemyCreation->start();
        Wavetimer->start();
        BoosterTimer->start();
        Player::movetime->start();
        Enemy::HitTimer->start();
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
        Enemy *enemy = new Enemy(RandPos, 0,20,100,1000);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    } else if (Edge == 1) {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(width(), RandPos,20,100,1000);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    } else if (Edge == 2) {
        RandPos = rand() % int(width());
        Enemy *enemy = new Enemy(RandPos, height(),20,100,1000);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    } else {
        RandPos = rand() % int(height());
        Enemy *enemy = new Enemy(0, RandPos,20,100,1000);
        addItem(enemy);
        connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
    }
}
