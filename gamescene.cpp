#include "gamescene.h"

GameScene::GameScene(double w, double h, int k)
    : gamemode(k)

{
    QPixmap bgPixmap(":/Imgs/Resources/GrassBackgorund.jpg"); // Replace ":/path/to/background.jpg" with the path to your background image
    setBackgroundBrush(bgPixmap.scaled(1280, 720));
    setSceneRect(0, 0, w, h);
    int game_rows = 9;
    int game_cols = 16;
    map.resize(game_rows);
    // resize the map
    for (int var = 0; var < map.size(); ++var) {
        map[var].resize(game_cols);
    }
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            map[i][j] = 0;
        }
    }
    map[4][7] = 1;
    map[3][7] = 2;
    // adding elements
    for (int var = 2; var < 7; ++var) {
        map[var][5] = 3;
        map[var][9] = 3;
    }
    for (int var = 5; var < 10; ++var) {
        map[2][var] = 3;
        map[6][var] = 3;
    }
    // display map
    DisplayMap();

    // i do not know if this is the best way

    // QTimer::singleShot(0, this, [this]() {
    //     for(int i = 0 ;i<3;i++){
    //         QObject::connect(timer, SIGNAL(timeout()), this, SLOT(createenemy()));
    //         timer->start(1000);
    //         QEventLoop loop;
    //         QTimer::singleShot(60000, &loop, SLOT(quit()));
    //         loop.exec();
    //     }
    // });
    // start();
    createenemy();
    // QObject::connect(timer, SIGNAL(timeout()), this, SLOT(createenemy()));
    // timer->start(1000);
    // createenemy();
}

void GameScene::DisplayMap()
{
    double yfactor = height() / map.size();
    double xfactor = width() / map[0].size();
    // Load the first image

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
             if (map[i][j] == 1) { // townall =1
                TownHall *a = new TownHall(xfactor, yfactor);
                a->setPos(j * xfactor, i * yfactor);
                x_townhall = j * xfactor;
                y_townhall = i * yfactor;
                a->SetHealth(this);
                addItem(a);
            } else if (map[i][j] == 3) { // fence = 3
                std::vector<int> a;
                if (map[i - 1][j] == 3) {
                    a.push_back(0);
                }
                if (map[i + 1][j] == 3) {
                    a.push_back(2);
                }
                if (map[i][j - 1] == 3) {
                    a.push_back(3);
                }
                if (map[i][j + 1] == 3) {
                    a.push_back(1);
                }
                Fence *fence = new Fence(xfactor, yfactor, a);
                fence->setPos(j * xfactor, i * yfactor);
                fence->SetHealth(this);
                addItem(fence);
            } else if (map[i][j] == 2) { // defence unit =2
                qDebug() << map[i][j] << yfactor << xfactor;
                DefenseUnit *a = new DefenseUnit(xfactor, yfactor, 1);
                x_cannon = j * xfactor;
                y_cannon = i * yfactor;
                a->setPos(x_cannon, y_cannon);
                a->SetHealth(this);
                addItem(a);
            }
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
    Bullet *a = new Bullet(x_cannon + 40, y_cannon + 40, mousePos.x(), mousePos.y());
    addItem(a);

}

void GameScene::start(){
    timer = new QTimer();

    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(createenemy()));
    timer->start(3000);
    // QEventLoop loop;
    // QTimer::singleShot(60000, &loop, SLOT(quit()));
    // loop.exec();

}

void GameScene::createenemy()
{
    int p;

    srand(time(0));
    // random generator of the enemies
        int n = rand()%4;

        if(n==0){
            p=rand()%1280;
            Enemy *enemy = new Enemy(p, 0, x_townhall, y_townhall);
            addItem(enemy);
            // QEventLoop loop;
            // QTimer::singleShot(2000, &loop, SLOT(quit()));
            // loop.exec();

        }
        else if(n==1){
            p=rand()%720;

            Enemy *enemy = new Enemy(1280, p, x_townhall, y_townhall);
            addItem(enemy);
            // QEventLoop loop;
            // QTimer::singleShot(2000, &loop, SLOT(quit()));
            // loop.exec();

        }
        else if(n==2){
            p=rand()%1280;

            Enemy *enemy = new Enemy(p, 720, x_townhall, y_townhall);
            addItem(enemy);
            // QEventLoop loop;
            // QTimer::singleShot(2000, &loop, SLOT(quit()));
            // loop.exec();

        }
        else if(n==3){
            p=rand()%720;

            Enemy *enemy = new Enemy(0, p, x_townhall, y_townhall);
            addItem(enemy);
            // QEventLoop loop;
            // QTimer::singleShot(2000, &loop, SLOT(quit()));
            // loop.exec();

        }
    }


