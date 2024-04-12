#include "health.h"

health::health(int h) {

    // Set rectangels

    healthrect = new QGraphicsRectItem(10,10,180,35,this);
    setRect(0,0,200,50);
    healthrect->setZValue(1);
    this->setZValue(0);

    // intialize health and brushes and adding them

    currentHealth = maxHealth = h;
    QBrush white(Qt::white);
    QBrush Green(Qt::green);
    healthrect->setBrush(Green);
    setBrush(white);
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
    float barWidth = float(currentHealth) / maxHealth * 200;
    healthrect->setRect(0, 0, barWidth, 50);
}
