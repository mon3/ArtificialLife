#include "being.h"


Being::Being(int _logX, int _logY)
  : logX(_logX), logY(_logY), isDead(false)
{

}

int Being::getHitPoints() const
{
    return hitPoints;
}

void Being::setHitPoints(int value)
{
    hitPoints = value;
}


int Being::getLogX() const
{
    return logX;
}

void Being::setLogX(int value)
{
    const int grSize = ParametersSet::getInstance()->getGridSize();
    if(value < grSize && value >= 0)
        logX = value;
}

int Being::getLogY() const
{
    return logY;
}

void Being::setLogY(int value)
{
    const int grSize = ParametersSet::getInstance()->getGridSize();
    if(value < grSize && value >= 0)
        logY = value;
}

bool Being::getIsDead() const
{
    return isDead;
}

void Being::setIsDead()
{
    isDead = true;
}


