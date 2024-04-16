#include "gamescene.h"

GameScene::GameScene(double w, double h, int k)
    : gamemode(k)

{
    QPixmap bgPixmap(
        ":/Imgs/Resources/GrassBackgorund.jpg"); // Replace ":/path/to/background.jpg" with the path to your background image
    setBackgroundBrush(bgPixmap.scaled(1280, 720));

    setSceneRect(0, 0, w, h);
    int game_rows = 9;
    int game_cols = 16;
    map.resize(game_rows);
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
    for (int var = 3; var < 6; ++var) {
        map[var][5] = 3;
        map[var][9] = 3;
    }
    for (int var = 6; var < 9; ++var) {
        map[2][var] = 3;
        map[6][var] = 3;
    }
    DisplayMap();
    time = new QTimer();
    QObject::connect(time, SIGNAL(timeout()), this, SLOT(createenemy()));
    time->start(2000);
}

void GameScene::DisplayMap()
{
    double yfactor = height() / map.size();
    double xfactor = width() / map[0].size();

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) {
                // qDebug() << map[i][j] << yfactor << xfactor;
                // Grass *a = new Grass(xfactor, yfactor);
                // a->setPos(j * xfactor, i * yfactor);

                // addItem(a);
            } else if (map[i][j] == 1) {
                // qDebug() << map[i][j] << yfactor << xfactor;
                TownHall *a = new TownHall(xfactor, yfactor);
                a->setPos(j * xfactor, i * yfactor);
                x_townhall = j * xfactor;
                y_townhall = i * yfactor;
                a->SetHealth(this);
                addItem(a);
            } else if (map[i][j] == 3) {
                // qDebug() << map[i][j] << yfactor << xfactor;
                Fence *a = new Fence(xfactor, yfactor);
                a->setPos(j * xfactor, i * yfactor);
                a->SetHealth(this);
                addItem(a);
            } else if (map[i][j] == 2) {
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

    // qDebug() << mousePos.x() << mousePos.y();
}

void GameScene::createenemy()
{
    // qDebug() << "spawn";
    Enemy *enemy = new Enemy(0, 0, x_townhall, y_townhall);
    addItem(enemy);
}

