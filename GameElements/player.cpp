#include "player.h"

Player::Player(int x , int y, int h,int s)
    :posx(x),posy (y), health(h),speed(s)
{
    setPos(x,y);
}

void Player::getdamage()
{
    if (!this->die()) {
        health = health - 50;
    }
}

bool Player::die()
{
    if (health <= 0) {
        delete this;
        return 1;
    }
    return 0;
}
