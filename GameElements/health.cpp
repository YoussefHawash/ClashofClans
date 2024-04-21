#include "health.h"

health::health(int x, int y, int w, int v)
    : x(x)
    , y(y - 5)
{
    // Set rectangels

    setRect(x, y, w, 3);

    setZValue(100);

    // intialize health and brushes and adding them

    currentHealth = maxHealth = v;

    QBrush Green(Qt::green);
    setBrush(Green);
}

void health::increasehealth(int i)
{
    if (currentHealth + i <= maxHealth) {
        currentHealth += i;
        updateHealthBar();
    } else {
        currentHealth = maxHealth;
        updateHealthBar();
    }

    //increasing health
}

void health::decreasehealth(int i)
{
    // decreasing health
    currentHealth -= i;
    updateHealthBar();
}




void health::updateHealthBar()
{
    // Scale to fit the width of the background
    float barWidth = (float(currentHealth) / maxHealth) * rect().width();
    setRect(x, y, barWidth, 3);
}

int health::gethealth()
{
    return currentHealth;
}
