#include "player.h"

Player::Player(int h)
    : health(h)
{}

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
