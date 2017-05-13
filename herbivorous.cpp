#include "herbivorous.h"





Being* Herbivorous::hunt()
{

    vector<Plant*> vec = ParametersSet::getInstance()->getAdjacentPlants(this);
    //no available plant at neighbourhood
    if(vec.empty()) {
        return nullptr;
    }

    //find most valuable plant
    Plant* p;
    int maxSugar = numeric_limits<int>::min();



    for(auto it = vec.begin(); it != vec.end(); ++it) {
        int temp = (*it)->getHitPoints();
        if(temp > maxSugar) {
            maxSugar = temp;
            p = *it;
        }
    }


    //if there is several max positions, select one randomly
    vector<Plant*> maxValuedPlants;
    copy_if(vec.cbegin(), vec.cend(), maxValuedPlants.begin(), [&](Plant* _p) -> bool {
       return _p->getHitPoints() == maxSugar;
    });
    maxValuedPlants.shrink_to_fit();
    size_t size = maxValuedPlants.size();
    if(size > 1)
        return maxValuedPlants[ParametersSet::getRandomInt() % size];

    return p;
}


void Herbivorous::eat(Being* b)
{
    Plant* p = static_cast<Plant*>(b);
    //check whether on your place there is plant
    this->saturationRate = 100.0f;
    p->setHitPoints(0);
    //if not, move to random place
    move();
}


