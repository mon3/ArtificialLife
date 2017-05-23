#include "animal.h"



void Animal::action()
{
    if(activity == Activity::DEAD)
        return;

    //else, look for a site with bigger "sugar" value
    Being* prey = hunt();

    //if there is a prey to hunt, go there and collect resources from site,
    if(prey != nullptr) {
        int goalX = prey->getLogX(),
            goalY = prey->getLogY();
        //unless you can reach prey in one turn, get as close as you could
        if(speed < eveSight) {
            // fix bug
            goalX = goalX + (speed - eveSight);
            goalY = goalY + (speed - eveSight);

        }
        move(goalX, goalY);

        eat(prey);
    }
    else // if no food, go to random adjacent place
        move();
    //for simplicity, assume that no exaustion is involved
    saturationRate -= metabolism;

    //animal is dead
    if(saturationRate < 0.0f) {
        activity = Activity::DEAD;
        return;
    }
}

void Animal::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Pressed!";
    emit callWindow(this);

}

void Animal::move(int x, int y )
{
    auto set = ParametersSet::getInstance();
    //move to random free location, within being reach
    if(x == UNKNOWN_LOCATION || y == UNKNOWN_LOCATION)
    {
        //todo: check neighbours
        const int gridSize = set->getGridSize();
        //set->getAdjacentBeings(this);
        int addVal = (ParametersSet::getRandomInt() % 3) - 1;
        this->setLogX(this->getLogX() + addVal);
        addVal = (ParametersSet::getRandomInt() % 3) - 1;
        this->setLogY(this->getLogY() + addVal);
        qDebug() << "isSet: " << this->getLogX() << " y: " << this->getLogY() << endl;
    } else
    {
        this->setLogX(x);
        this->setLogY(y);
    }

}

float Animal::getMetabolism() const
{
    return metabolism;
}

int Animal::getFood_capacity() const
{
    return food_capacity;
}

void Animal::setFood_capacity(int value)
{
    food_capacity = value;
}

float Animal::getSaturationRate() const
{
    return saturationRate;
}

void Animal::setSaturationRate(float value)
{
    saturationRate = value;
}

int Animal::getEveSight() const
{
    return eveSight;
}

