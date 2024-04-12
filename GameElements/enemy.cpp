#include "enemy.h"

Enemy::Enemy(int x, int y)
    : Player(500)
    , posx(x)
    , posy(y)
{
    setPixmap(QPixmap(":/pics/Troop.png").scaled(20, 20));
    movetime = new QTimer();
    connect(movetime, SIGNAL(timeout()), this, SLOT(move()));
    movetime->start(1000);
}

void Enemy::move()
{
    bool c;
    srand(time(0));
    if ((posx == 7 && posy == 4) || (posx == 8 && posy == 4)) {
        dealdamage();
    } else {
        c = rand() / 2;
        if ((posx != 7 && posy != 4) || (posx != 8 && posy != 4)) {
            if (c) {
            }
        }
        if (posx == 7) {
            if (posy > 4) {
                posy--;
            }
            if (posy < 4) {
                posy++;
            }
        } else if (posy == 4) {
            if (posx > 8) {
                posx--;
            }
            if (posx < 7) {
                posx++;
            }
        }
    }
}

void Enemy::dealdamage() {}
