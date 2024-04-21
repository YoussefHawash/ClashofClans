#include "gamescene.h"
#include <QLabel>
#include <QVBoxLayout>

GameScene::GameScene(double w, double h)

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
    start();
}

void GameScene::DisplayMap()
{
    double yfactor = height() / map.size();
    double xfactor = width() / map[0].size();

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
             if (map[i][j] == 1) { // townall =1
                 TownHall *townhall = new TownHall(xfactor, yfactor);
                 x_townhall = j * xfactor;
                 y_townhall = i * yfactor;
                 townhall->setPos(x_townhall, y_townhall);
                 townhall->SetHealth(this, 5000);
                 addItem(townhall);
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
                fence->SetHealth(this, 4000);
                addItem(fence);
            } else if (map[i][j] == 2) { // defence unit =2
                qDebug() << map[i][j] << yfactor << xfactor;
                DefenseUnit *a = new DefenseUnit(xfactor, yfactor, 1);
                x_cannon = j * xfactor;
                y_cannon = i * yfactor;
                a->setPos(x_cannon, y_cannon);
                addItem(a);

            }
        }
    }
    townworkers *workers[3];
    for(int i= 0 ; i <3;i++){
        workers[i] = new townworkers((x_townhall-80)+(i*200),y_townhall);
        addItem(workers[i]);
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


void GameScene::Gameover()
{
    EndWave();
    QMediaPlayer *sound = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    sound->setSource(QUrl("qrc:/sounds/Resources/Voicy_Barbarian death cry - Clash of Clans.mp3"));
    sound->setAudioOutput(audioOutput);
    audioOutput->setVolume(50);
    sound->play();
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("serif", 48));
    gameOverText->setPlainText("GAME OVER!");
    gameOverText->setPos(width() / 2 - 180, height() / 2 - 48);
    addItem(gameOverText);
}

void GameScene::EndWave()
{
    QObject::disconnect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createenemy()));
    clear();
}
void GameScene::start(){
    EnemyCreation = new QTimer();
    QObject::connect(EnemyCreation, SIGNAL(timeout()), this, SLOT(createenemy()));
    EnemyCreation->start(4000);
    QTimer *Wavetimer = new QTimer();
    QObject::connect(Wavetimer, SIGNAL(timeout()), this, SLOT(EndWave()));
    Wavetimer->start(60000);
}

void GameScene::createenemy()
{
    int RandPos;

    srand(time(0));
    // random generator of the enemies
    int Edge = rand() % 4;

    if (Edge == 0) {
        RandPos = rand() % 1280;
        Enemy *enemy = new Enemy(RandPos, 0, x_townhall, y_townhall, 100);
        addItem(enemy);
    } else if (Edge == 1) {
        RandPos = rand() % 720;
        Enemy *enemy = new Enemy(1280, RandPos, x_townhall, y_townhall, 100);
        addItem(enemy);

    } else if (Edge == 2) {
        RandPos = rand() % 1280;
        Enemy *enemy = new Enemy(RandPos, 720, x_townhall, y_townhall, 100);
        addItem(enemy);

    } else if (Edge == 3) {
        RandPos = rand() % 720;
        Enemy *enemy = new Enemy(0, RandPos, x_townhall, y_townhall, 100);
        addItem(enemy);
    }
    }


