#include "predator.h"





Being* Predator::hunt()
{
    ParametersSet* set = ParametersSet::getInstance();
    vector<Herbivorous*> prey = set->getAdjacentBeings<Herbivorous>(this, getSpeed());
    qDebug() << "in adj func";
    //TODO: add logic

    return nullptr;
}


void Predator::eat(Being *)
{

}


vector<Animal*> Predator::findEnemies()
{
    //does nothing
    return vector<Animal*>();
}
