#include "herbivorous.h"





Being* Herbivorous::hunt()
{
    vector<Plant*> vec = ParametersSet::getInstance()->getAdjacentBeings(this, getSpeed());
    //no available plant at neighbourhood
    if(vec.empty()) {
        return nullptr;
    }

    //find most valuable plant
    Plant* p = nullptr;
    int maxSugar = numeric_limits<int>::min();


    //find which plant is most valued
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        int temp = (*it)->getHitPoints();
        if(temp > maxSugar) {
            maxSugar = temp;
            p = *it;
        }
    }

    // test whether there are several posiotions with max faculty
    vector<Plant*> maxValuedPlants;

    copy_if(vec.begin(), vec.end(), std::back_inserter(maxValuedPlants), [&](Plant* _p) -> bool {
       return _p->getHitPoints() == maxSugar;
    });

    maxValuedPlants.shrink_to_fit();

    //if there is several max positions, select one randomly
    size_t size = maxValuedPlants.size();
    if(size > 1)
        return maxValuedPlants[ParametersSet::getRandomInt(0, size)];

    return p;
}

// ask if correct
void Herbivorous::eat(Being* b)
{
    Plant* p = qobject_cast<Plant*>(b);
    int plantWealth = p->getHitPoints();
    foodConsumptionRule(plantWealth);
    p->setHitPoints(plantWealth);

}




vector<Animal*> Herbivorous::findEnemies()
{
    return vector<Animal*>();
}
