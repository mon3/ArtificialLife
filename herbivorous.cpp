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
        return maxValuedPlants[ParametersSet::getRandomInt() % size];

    return p;
}

// ask if correct
void Herbivorous::eat(Being* b)
{
    Plant* p = qobject_cast<Plant*>(b);
    ParametersSet* set = ParametersSet::getInstance();
    float currentSaturationRate = this->getSaturationRate();
    int plantWealth = p->getHitPoints();
    // TODO: set max saturation value
    if(currentSaturationRate + plantWealth < 100.0f)
    {
        // if a whole plant is not enough to satisfy hunger, just eat it all
        this->setSaturationRate(currentSaturationRate + plantWealth);
        plantWealth = 0;
    }
    else
    {
        int delta = 100.0f - currentSaturationRate;
        this->setSaturationRate(100.0f);
        plantWealth -= delta;

        int currentFoodCapacity = this->getFoodCapacity();

        // try to take as many plants as you can
        const int maxFoodCapacity = set->getMaxFoodCapacity();
        if(currentFoodCapacity + plantWealth < maxFoodCapacity)
        {
            this->setFoodCapacity(currentFoodCapacity + plantWealth);
            plantWealth = 0;
        }
        else
        {
            // if not, fill up your food cap
            plantWealth -= set->getMaxFoodCapacity() - currentFoodCapacity;
            this->setFoodCapacity(maxFoodCapacity);
        }

    }
    p->setHitPoints(plantWealth);

}




vector<Animal*> Herbivorous::findEnemies()
{
    return vector<Animal*>();
}
