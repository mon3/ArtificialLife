#include "animal.h"



void Animal::action()
{
    if(activity == Activity::DEAD)
        return;

    //else, look for a site with bigger "sugar" value





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

void Animal::move()
{
    //todo: check neighbours
    const int gridSize = ParametersSet::getInstance()->getGridSize();
    int addVal = (ParametersSet::getRandomInt() % 3) - 1;
    this->setLogX(this->getLogX() + addVal);
    addVal = (ParametersSet::getRandomInt() % 3) - 1;
    this->setLogY(this->getLogY() + addVal);
    qDebug() << "isSet: " << this->getLogX() << " y: " << this->getLogY() << endl;
}

int Animal::getEveSight() const
{
    return eveSight;
}

