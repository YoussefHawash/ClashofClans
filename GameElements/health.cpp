#include "health.h"

health::health(int a, int b, int w, int v)
    : x(a + 10)
    , y(b)
{
    // Set rectangels

    setRect(x, y, w - 20, 5);

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

bool health::decreasehealth(int i)
{

    // checking if died and if so return 0
    if(currentHealth-i <= 0){
        return 0;
    }

    // decreasing health

    else{
        currentHealth = currentHealth-i;
        updateHealthBar();
        return 1;
    }
}




void health::updateHealthBar()
{
    // Scale to fit the width of the background
    float barWidth = (float(currentHealth) / maxHealth) * rect().width();

    setRect(x, y, barWidth, 5);
}
