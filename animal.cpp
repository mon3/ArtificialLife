#include "animal.h"



void Animal::action()
{
    move();
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

