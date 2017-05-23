#include "animal.h"



void Animal::action()
{
    if(activity == Activity::DEAD)
        return;

    // first, check for enemies

    //if there any, run to safe(seems to) place

    //if there not, hunt


    //else, look for a site with bigger "sugar" value
    Being* prey = hunt();

    //if there is a prey to hunt, go there and collect resources from site,
    if(prey != nullptr) {
        Activity = HUNTING;
        int goalX = prey->getLogX(),
            goalY = prey->getLogY();

        //unless you can reach prey in one turn, get as close as you could
        if(speed < eveSight) {
            // how far we can reach
            int delta = speed - eveSight;
            goalX = goalX + (speed - eveSight);
            goalY = goalY + (speed - eveSight);

        } else {
            move(goalX, goalY);
            eat(prey);
        }
    } else {
        // if no food, go to random adjacent place,
        // we assume, that this place should be as far, as being could reach, to increase chance of finding food
        move();
    }

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
        // first, check being activity, if hungry - go as far
        // as you could, else do not go far away
        //todo: check neighbours
        const int gridSize = set->getGridSize();
        vector<Animal*> occupiedPlaces = set->getAdjacentBeings<Animal>(this);


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

int Animal::getFoodCapacity() const
{
    return foodCapacity;
}

void Animal::setFoodCapacity(int value)
{
    foodCapacity = value;
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

