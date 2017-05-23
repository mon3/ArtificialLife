#include "predator.h"





Being* Predator::hunt()
{
    ParametersSet* set = ParametersSet::getInstance();
    vector<Herbivorous*> prey = set->getAdjacentBeings<Herbivorous>(this);
    qDebug() << "in adj func";
    //TODO: add logic

    return nullptr;
}


void Predator::eat(Being *)
{
}
