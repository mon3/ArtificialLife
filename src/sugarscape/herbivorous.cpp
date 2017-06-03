#include "herbivorous.h"



Herbivorous::Herbivorous(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity, int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs):Animal(x,y)
{
    setHitPoints(hitPoints);
    setEyeSight(eyeSight);
    setAge(age);
    setGeneration(generation);
    setSpeed(speed);
    setFoodCapacity(foodCapacity);
    setMetabolism(metabolism);
    setExhaustionLevel(exhaustionLevel);
    setSaturationRate(saturationRate);
    setStdDevs(stdDevs);
}


Herbivorous::Herbivorous(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism, int foodCapacity, int exhaustionLevel, QVector<double> stdDevs):Animal(x, y)
{
    setEyeSight(eyeSight);
    setSpeed(speed);
    setHitPoints(hitPoints);
    setMetabolism(metabolism);
    setFoodCapacity(foodCapacity);
    setExhaustionLevel(exhaustionLevel);
    setStdDevs(stdDevs);
}


Herbivorous::Herbivorous(int x, int y, QVector<int> features, QVector<double> stdDevs):Animal(x, y)
{
    setFeaturesEA(features, Beings::HERBIVOROUS);
    setStdDevs(stdDevs);
}


//Being* Herbivorous::hunt()
Being* Herbivorous::hunt()
{
    std::vector<Plant*> vec = ParametersSet::getInstance()->getAdjacentBeings(this->getLogX(), this->getLogY(), getSpeed());
    //no available plant at neighbourhood
    if(vec.empty()) {
        return nullptr;
    }

    //find most valuable plant
    Plant* p = nullptr;
    int maxSugar = std::numeric_limits<int>::min();


    //find which plant is most valued
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        int temp = (*it)->getHitPoints();
        if(temp > maxSugar) {
            maxSugar = temp;
            p = *it;
        }
    }

    // test whether there are several posiotions with max faculty
    std::vector<Plant*> maxValuedPlants;

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(maxValuedPlants), [&](Plant* _p) -> bool {
       return _p->getHitPoints() == maxSugar;
    });

    maxValuedPlants.shrink_to_fit();

    //if there is several max positions, select one randomly
    auto size = maxValuedPlants.size();
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




std::vector<Animal*> Herbivorous::findEnemies()
{
    return std::vector<Animal*>();
}


void Herbivorous::accept(Visitor * v)
{
    v->visit(this);
}
