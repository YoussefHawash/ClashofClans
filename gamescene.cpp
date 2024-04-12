#include "gamescene.h"

GameScene::GameScene(double w, double h, int k)
    : gamemode(k)

{
    setSceneRect(0, 0, w, h);

    // if (k == 1) {
    //     for (int i = 0; i < 9; i++) {
    //         for (int j = 0; j < 16; j++) {
    //             if (j < 3 || i < 3 || j > 12 || i > 5) {
    //                 // enemies can spawn
    //                 map[i][j] = -1;
    //             } else {
    //                 map[i][j] = 0;
    //             }
    //         }
    //     }
    // time = new QTimer();
    // connect(time, SIGNAL(timeout()), this, SLOT(createEnemy()));
    // time->start(2000);
    // }
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            map[i][j] = 0;
        }
    }

    DisplayMap();
}

void GameScene::createEnemy()
{
    int x, y;
    bool c1, c2;
    c1 = QRandomGenerator::global()->bounded(0, 1);
    c2 = QRandomGenerator::global()->bounded(0, 1);
    if (c1) {
        x = QRandomGenerator::global()->bounded(0, 3);
        if (c2) {
            y = QRandomGenerator::global()->bounded(0, 3);
        } else {
            y = QRandomGenerator::global()->bounded(6, 8);
        }
    } else {
        x = QRandomGenerator::global()->bounded(13, 15);
        if (c2) {
            y = QRandomGenerator::global()->bounded(0, 3);
        } else {
            y = QRandomGenerator::global()->bounded(6, 8);
        }
    }
    // int addy = QRandomGenerator::global()->bounded(3,5);
    // int addx = QRandomGenerator::global()->bounded(3,5);
    // int x = QRandomGenerator::global()->bounded(3,12);
    // int y = QRandomGenerator::global()->bounded(3,5);

    // 4 means troop
    map[x][y] = 4;
    Enemy(x, y);
}

void GameScene::DisplayMap()
{
    double yfactor = height() / 18;
    double xfactor = width() / 32;

    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (map[i][j] == 0) {
                // qDebug() << map[i][j] << yfactor << xfactor;
                Grass *a = new Grass;
                QPixmap grass(":/Imgs/Resources/GrassChunk.jpg");
                grass = grass.scaled(xfactor, yfactor);
                a->setPixmap(grass);
                a->setPos(j * xfactor, i * yfactor);
                //a->setPen(Qt::NoPen);
                addItem(a);
            }
        }
    }
}
