#include "plant.h"



void Plant::action()
{
    ParametersSet* set = ParametersSet::getInstance();
    //for each turn
    int hp = getHitPoints(),
        delta = set->getPlantGrowbackLevel(),
        maxHp = set->getMaxPlantHp();
    if(hp + delta < maxHp)
        setHitPoints(hp + delta);
    else
        setHitPoints(maxHp);
}


Qt::GlobalColor Plant::getPenColor() const
{
    return Qt::blue;
}


void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->setBrush(getPenColor());
    painter->drawEllipse(this->rect());
}
