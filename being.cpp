#include "being.h"


Being::Being(int _logX, int _logY)
  : QGraphicsRectItem(0, 0, ParametersSet::BEING_WIDTH, ParametersSet::BEING_WIDTH), logX(_logX), logY(_logY)
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
    int grSize = ParametersSet::getInstance()->getGridSize();
    if(value < grSize && value >= 0)
        logX = value;
}

int Being::getLogY() const
{
    return logY;
}

void Being::setLogY(int value)
{
    int grSize = ParametersSet::getInstance()->getGridSize();
    if(value < grSize && value >= 0)
        logY = value;
}

void Being::updateBeing()
{
    ParametersSet* set = ParametersSet::getInstance();
    int oldX = logX,
        oldY = logY;

    this->action();

    if(oldX != logX || oldY != logY)
        set->mapPosition(this);
}

void Being::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillRect(this->rect(), getPenColor());
}
