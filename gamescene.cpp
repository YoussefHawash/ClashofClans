#include "gamescene.h"
#include "GameElements/bullet.h"
#include "GameElements/enemy.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "booster.h"
#include <random>
GameScene::GameScene(int level, double w, double h)
    : Wavenum(1)
    , WaveTime(60)
    , CreationFrequency(10000 / (level + 1))
    , gamelevel(level)
    , clickable(true)
{
    Wavetimer = new QTimer();
    BoosterCreationTimer = new QTimer();
    Enemy::HitTimer->start(1000);
    //Setting Up the Scene
    QPixmap bgPixmap(":/Imgs/Resources/GrassBackgorund.jpg");
    setBackgroundBrush(bgPixmap.scaled(w, h));
    setSceneRect(0, 0, w, h);
    WaveInfo = new QGraphicsTextItem();
    TimeInfo = new QGraphicsTextItem();
    TogglePause = new QGraphicsTextItem();
    BoostInfo = new QGraphicsTextItem();
    EventWindow = new QGraphicsPixmapItem;
    NextwaveText = new QGraphicsTextItem;
    NextwaveTextNav = new QGraphicsTextItem;
    BoostInfo = new QGraphicsTextItem();
    //BlackWindow In case
    QPixmap pause(":/Imgs/Resources/pause.png");
    EventWindow->setPixmap(pause.scaled(100,100));
    EventWindow->setPos((width()-100) / 2, (height()-100) / 2);
    EventWindow->setZValue(5);
    EventWindow->hide();
    //Wave Info
    WaveInfo->setDefaultTextColor(Qt::black);
    WaveInfo->setFont(QFont("serif", 16));
    WaveInfo->setPos(0, 0);
    // Wave Timer
    TimeInfo->setDefaultTextColor(Qt::black);
    TimeInfo->setFont(QFont("serif", 16));
    TimeInfo->setPlainText(QString("Time Remaining : %1").arg(WaveTime));
    TimeInfo->setPos(0, 25);
    //Pause Nav
    TogglePause->setDefaultTextColor(Qt::black);
    TogglePause->setFont(QFont("serif", 16));
    TogglePause->setPlainText("[Escape] To Pause");
    TogglePause->setPos(0, 48);
    //Booster Timer
    BoostInfo->setDefaultTextColor(Qt::black);
    BoostInfo->setFont(QFont("serif", 16));
    BoosterIntervalTimer = new QTimer;
    BoostInfo->setPos(0, 75);
    BoostInfo->hide();
    //Next Wave Info
    NextwaveText->setDefaultTextColor(Qt::white);
    NextwaveText->setFont(QFont("serif", 48));

    NextwaveText->setZValue(10);
    NextwaveText->setPos(width() / 2 - 180, height() / 2 - 48);
    NextwaveTextNav->setPlainText("[Enter] Next Wave \n[Escape] Retrun To MainMenu");
    NextwaveTextNav->setDefaultTextColor(Qt::black);
    NextwaveTextNav->setFont(QFont("serif", 16));
    NextwaveTextNav->setPos(width() / 2 - 180, height() / 2 + 48);
    NextwaveTextNav->hide();
    NextwaveText->hide();
    //Adding Items to Scene
    addItem(NextwaveText);
    addItem(NextwaveTextNav);
    addItem(TimeInfo);
    addItem(WaveInfo);
    addItem(TogglePause);
    addItem(BoostInfo);
    addItem(EventWindow);
    // Rendering Map
    RenderingMap();
    //Starting the Waves
    StartWave();
}
void GameScene::RenderingMap()
{
    //Clearing the Map In Case
    map.clear();
    //Sizing Set up
    map.resize(9);
    yfactor = height() / 9;
    xfactor = width() / 16;
    //Reading The File
    //Rendering map
    QFile file(":/maps/Resources/map" + QString::number(gamelevel) + ".txt");
    if (!file.open(QIODevice::ReadOnly)) {
    }
    else {
        QTextStream in(&file);
        int row(0), column(0);
        while (!in.atEnd() && row != 9) {
            int value;
            in >> value;
            Node *node=new Node(row,column,0,0);
            if(value==0)
            {
                //Empty Chunck
                node->weight= 1;
                node->type=0;
            }
            else if (value ==1)
            {
                // Towhall Chunck
                node->type=1;
                node->weight=100;
            }
            else if (value ==2)
            {
                // Defense Unit Chunck
                node->weight=1;
                node->type=2;
            }
            else{
                // Fence Chunck
                node->weight=90;
                node->type=3;
            }

            map[row].push_back(node);

            if (column == 15)
            {
                column = 0;
                row++;
            }
            else
                column++;

        }


        //Adding Items
        for (int i = 0; i < int(map.size()); ++i) {
            for (int j = 0; j < int(map[i].size()); ++j) {
                if (map[i][j]->type == 1)
                {
                    // TownHall
                    townhall = new TownHall(this, j * xfactor, i * yfactor );
                    addItem(townhall);
                }
                else if (map[i][j]->type == 3) {
                    //Fence
                    //Setting The fence Walls to be rendered
                    vector<int> *Edges = new vector<int>;
                    if (map[i - 1][j]->type == 3) {
                        Edges->push_back(0);
                    }
                    if (map[i + 1][j]->type ==3) {
                        Edges->push_back(2);
                    }
                    if (map[i][j - 1]->type ==3) {
                        Edges->push_back(3);
                    }
                    if (map[i][j + 1]->type == 3) {
                        Edges->push_back(1);
                    }
                    Fence *fence = new Fence(this, j * xfactor, i * yfactor, *Edges);
                    delete Edges;
                    addItem(fence);
                    fences.push_back(fence);
                }
                else if (map[i][j]->type == 2)
                {
                    // Defense Unit
                    Cannon = new DefenseUnit(this, j * xfactor, i * yfactor, gamelevel);
                    addItem(Cannon);
                }
            }
        }
        //Dijekstra Set adding heiraricy
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 16; ++j)
            {
                map[i][j]->weight+=sqrt(pow(int(townhall->y()/xfactor)-i,2)+pow(int(townhall->x()/xfactor)-j,2));
            }
        }
        //Adding Civilians
        townworker1= new townworkers;
        townworker2= new townworkers;
        townworker1->setPos(7*80,4*80);
        townworker2->setPos(7*80,4*80);

        addItem(townworker1);
        addItem(townworker2);
        townworker1->hide();
        townworker2->hide();
    }
}
void GameScene::StartWave()
{
    WaveTime = 60;
    clickable = true;
    if (NextwaveText->isVisible()) {
        NextwaveText->hide();
        NextwaveTextNav->hide();
    }
    //Update wave label
    WaveInfo->setPlainText(QString("Wave # %1").arg(Wavenum));
    //Show HUD
    WaveInfo->show();
    TimeInfo->show();
    TogglePause->show();
    //Setting Timers
    connect(BoosterCreationTimer, SIGNAL(timeout()), this, SLOT(createBooster()));
    connect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
    connect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    connect(Wavetimer, SIGNAL(timeout()), this, SLOT(checkfences()));
    EnemyCreation->start(CreationFrequency);
    Wavetimer->start(1000);
    BoosterCreationTimer->start(20000);
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
        disconnectTimers();
        //Displaying
        NextwaveText->setPlainText(QString(QString("Wave %1 Ended").arg(Wavenum)));
        NextwaveText->show();
        NextwaveTextNav->show();
        CreationFrequency = (CreationFrequency * 4) / (5);
    } else {
        WaveTime--;
        TimeInfo->setPlainText(QString("Time Remaining : %1").arg(WaveTime));
    }
}
void GameScene::Gameover(bool state = 0)
{
    WaveTime = 0;
    clickable = false;
    disconnectTimers();
    // Clean up any existing items
    clearEnemies();

    for (int i = items().size() - 1; i >= 0; --i) {
        if (Building *building = dynamic_cast<Building *>(items().at(i))) {
            delete building;
        }
    }
    townworker1->hide();
    townworker2->hide();
    GameOverText = new QGraphicsTextItem();
    Navigation = new QGraphicsTextItem();
    GameOverText->setFont(QFont("serif", 48));
    GameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
    Navigation->setFont(QFont("serif", 16));
    Navigation->setPos(width() / 2 - 180, height() / 2 + 48);
    if (state) {
        // Display game over text
        GameOverText->setDefaultTextColor(Qt::green);
        GameOverText->setPlainText(QString("Level %1 Victory!").arg(gamelevel));
        if (gamelevel < 5) {
            Navigation->setPlainText("[Enter] Next level \n[Escape] Retrun To MainMenu");
            Navigation->show();
        }
    } else {
        // Display game over text
        Wavenum=0;
        GameOverText->setDefaultTextColor(Qt::red);
        GameOverText->setPlainText("GAME OVER!");
        Navigation->setPlainText("[Escape] MainMenu");
        Navigation->show();
    }
    addItem(Navigation);
    addItem(GameOverText);

}
void GameScene::MoveToNextLevel()
{
    // hiding all gameover elements
    fences.clear();
    GameOverText->hide();
    Navigation->hide();
    //Logic of Game End
    delete townworker1;
    delete townworker2;
    gamelevel++;
    if (gamelevel < 5) {
        CreationFrequency = 10000/(gamelevel+1);
        Wavenum = 1;
        RenderingMap();
        StartWave();
    }
    else
        return Gameover(1);


}
// Staginng Func
void GameScene::clearEnemies()
{
    for (int i = items().size() - 1; i >= 0; --i) {
        if (Enemy *enemy = dynamic_cast<Enemy *>(items().at(i))) {
            delete enemy;
        }
    }
}
//Timer Realated

void GameScene::createEnemy()
{
    int RandPos;
    srand(time(0));
    // random generator of the enemies
    int Edge = rand() % 4;
    Enemy *enemy;
    RandPos = rand() % int(width());


    if (Edge == 0) {
        RandPos = rand() % int(width());
        enemy = new Enemy(RandPos, 0,20,100,1000);
    } else if (Edge == 1) {
        RandPos = rand() % int(height());
        enemy = new Enemy(width(), RandPos,20,100,1000);
    } else if (Edge == 2) {
        RandPos = rand() % int(width());
        enemy = new Enemy(RandPos, height(),20,100,1000);
    } else {
        RandPos = rand() % int(height());
        enemy = new Enemy(0, RandPos,20,100,1000);
    }
    addItem(enemy);
    connect(enemy, &Enemy::TownhallDestroyed, this, &GameScene::Gameover);
}
void GameScene::disconnectTimers(){
    disconnect(BoosterIntervalTimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    disconnect(Wavetimer, SIGNAL(timeout()), this, SLOT(checkfences()));
    disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createEnemy()));
    disconnect(BoosterCreationTimer, SIGNAL(timeout()), this, SLOT(createBooster()));
};
void GameScene::createBooster()
{
    // Randomizing Boost Location
    random_device rnd;
    mt19937 gen(rnd());
    uniform_real_distribution<double> distribX(0.0, width());
    uniform_real_distribution<double> distribY(0.0, height());
    Booster* boost = new Booster( distribX(gen), distribY(gen));
    addItem(boost);

}
void GameScene::BoosterCountDown()
{
    if(BoosterActivated){
        // Boost Timing
        if(BoostTime>0)
        {
            BoostInfo->setPlainText(QString("Boost Time Remaining : %1").arg(--BoostTime));
        }
        else
        {
            BoosterActivated=false;
            BoostInfo->hide();
            disconnect(BoosterIntervalTimer, SIGNAL(timeout()), this, SLOT(BoosterCountDown()));
        }
    }


}
void GameScene::checkfences()
{
    for(int i =0; i<int(fences.size());i++){
        if(fences[i]->isVisible()){
        if(!fences[i]->On_Repair&&fences[i]->gethealth()->gethealth() < 80 ){
            if(townworker1->Avaliable && !townworker1->dead)
            {townworker1->show();
                townworker1->SetTarget(fences[i]);
            }

            else if(townworker2->Avaliable && !townworker2->dead)
            {townworker2->show();
                townworker2->SetTarget(fences[i]);
            }

        }}

        }

}

//Input Related Func
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
        Bullet *bullet = new Bullet(Cannon->x() + (xfactor / 2),
                                    Cannon->y() + (yfactor / 2),
                                    mousePos.x(),
                                    mousePos.y(),BoosterActivated);
        addItem(bullet);
        connect(bullet, SIGNAL(BoostHit()), this, SLOT(BoosterActivate()));
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
            StartWave();}
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
        Player::movetime->stop();
        EnemyCreation->stop();
        Wavetimer->stop();
        BoosterCreationTimer->stop();
        Enemy::HitTimer->stop();
        BoosterIntervalTimer->stop();
    } else {
        TogglePause->setPlainText("[Escape] To Pause");
        EventWindow->hide();
        clickable = true;
        EnemyCreation->start();
        Wavetimer->start();
        Player::movetime->start();
        BoosterCreationTimer->start();
        BoosterIntervalTimer->start();
        Enemy::HitTimer->start();
    }
}
void GameScene::BoosterActivate() {
    BoostTime=10;
    BoostInfo->setPlainText(QString("Boost Time Remaining : %1").arg(BoostTime));
    if(!BoosterActivated)
    {
        BoostInfo->show();
        BoosterIntervalTimer->start(1000);
        connect(BoosterIntervalTimer, SIGNAL(timeout()), this, SLOT(BoosterCountDown()));
        BoosterActivated = true;
    }

};

//Getters
TownHall *GameScene::gettownhall() {
    return townhall;
};
