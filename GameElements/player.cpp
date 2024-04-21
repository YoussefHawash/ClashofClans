#include "player.h"

Player::Player(int x , int y, int h,int s)
    :posx(x),posy (y), health(h),speed(s)
{
    setPos(x,y);
}

void Player::getdamage(int i)
{
    if (!this->die()) {
        health = health - i;
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
