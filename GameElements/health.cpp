#include "health.h"

health::health(int x, int y, int w, int hp)
    : x(x)
    , y(y - 5)
    , originalwidth(w)
{
    // Set rectangels

    setRect(x, y, w, 3);

    setZValue(100);

    // intialize health and brushes and adding them

    currentHealth = maxHealth = hp;

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
    // S cale to fit the width of the background
    float barWidth = (float(currentHealth) / maxHealth) * originalwidth;
    setRect(x, y, barWidth, 3);
    if (float(currentHealth / maxHealth) < 1 && float(currentHealth / maxHealth) >= 0.5) {
        QBrush yellow(Qt::yellow);
        setBrush(yellow);
    } else if ( float(currentHealth / maxHealth) < 0.5){
        QBrush red(Qt::red);
        setBrush(red);
    }
    else
    {        QBrush green(Qt::green);
        setBrush(green); }
}

int health::gethealth()
{
    return currentHealth;
}
