#include "health.h"

health::health(int a, int b, int w, int v)
    : x(a)
    , y(b - 5)
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
    //check full health

    if(currentHealth!= maxHealth){}

    //increasing health

    else if(currentHealth+i <= maxHealth){
        currentHealth = currentHealth + i;
        updateHealthBar();
    }
    else{
        currentHealth = maxHealth;
        updateHealthBar();
    }
}

void health::decreasehealth(int i)
{
    // decreasing health

    currentHealth = currentHealth - i;
    updateHealthBar();
}




void health::updateHealthBar()
{
    // Scale to fit the width of the background
    float barWidth = (float(currentHealth) / maxHealth) * rect().width();

    setRect(x, y, barWidth, 5);
}

int health::gethealth()
{
    return currentHealth;
}
