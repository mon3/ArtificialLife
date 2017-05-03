#include "being.h"


Being::Being(int _logX, int _logY)
  : QGraphicsRectItem(0, 0, WIDTH, WIDTH), logX(_logX), logY(_logY)
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

void Being::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     painter->setPen(Qt::red);
     painter->drawRect(this->rect());
}

int Being::getLogX() const
{
    return logX;
}

void Being::setLogX(int value)
{
    logX = value;
}

int Being::getLogY() const
{
    return logY;
}

void Being::setLogY(int value)
{
    logY = value;
}
