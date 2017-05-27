#include "predator.h"





Being* Predator::hunt()
{
    qDebug() << "here1";
    vector<Herbivorous*> vec = ParametersSet::getInstance()->
            getAdjacentBeings<Herbivorous*>(this, getEveSight());
    //no available plant at neighbourhood
    if(vec.empty()) {
        return nullptr;
    }

    //find most valuable plant
    Herbivorous* p = nullptr;
    int maxSugar = numeric_limits<int>::min();


    //find which plant is most valued
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        int temp = (*it)->getHitPoints();
        if(temp > maxSugar) {
            maxSugar = temp;
            p = *it;
        }
    }
    qDebug() << "here2";
    // test whether there are several posiotions with max faculty
    vector<Herbivorous*> maxValuedPlants;

    copy_if(vec.begin(), vec.end(), std::back_inserter(maxValuedPlants), [&](Herbivorous* _p) -> bool {
       return _p->getHitPoints() == maxSugar;
    });

    maxValuedPlants.shrink_to_fit();

    //if there is several max positions, select one randomly
    size_t size = maxValuedPlants.size();
    if(size > 1)
        return maxValuedPlants[ParametersSet::getRandomInt(0, size)];
    qDebug() << "here3";
    return p;
}


void Predator::eat(Being * b)
{
    Herbivorous* herb = qobject_cast<Herbivorous*>(b);
    int herbValue = herb->getHitPoints();
    foodConsumptionRule(herbValue);
    // after eating, herb. is removed from board
    ParametersSet::getInstance()->removeBeing(herb);
}


vector<Animal*> Predator::findEnemies()
{
    //does nothing
    return vector<Animal*>();
}
