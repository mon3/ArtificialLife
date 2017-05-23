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
