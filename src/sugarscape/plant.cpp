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





void Plant::accept(Visitor *v)
{
    v->visit(this);
}
