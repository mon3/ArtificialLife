#include "animal.h"



void Animal::action()
{
    if(activity == Activity::DEAD)
        return;

    //else, look for a site with bigger "sugar" value
    Being* prey = hunt();

    //if there is a prey to hunt, go there and collect resources from site,
    if(prey != nullptr) {
        move(prey->getLogX(), prey->getLogY());
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
    if(x == UNKNOWN_LOCATION || y == UNKNOWN_LOCATION)
    {
        //todo: check neighbours
        const int gridSize = ParametersSet::getInstance()->getGridSize();
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

int Animal::getEveSight() const
{
    return eveSight;
}

