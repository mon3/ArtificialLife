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
//{

//    vector<Plant*> vec = ParametersSet::getInstance()->getAdjacentPlants(this);
//    //no available plant at neighbourhood
//    if(vec.empty()) {
//        return nullptr;
//    }

//    //find most valuable plant
//    Plant* p;
//    int maxSugar = numeric_limits<int>::min();



//    for(auto it = vec.begin(); it != vec.end(); ++it) {
//        int temp = (*it)->getHitPoints();
//        if(temp > maxSugar) {
//            maxSugar = temp;
//            p = *it;
//        }
//    }


//    //if there is several max positions, select one randomly
//    vector<Plant*> maxValuedPlants;
//    copy_if(vec.cbegin(), vec.cend(), maxValuedPlants.begin(), [&](Plant* _p) -> bool {
//       return _p->getHitPoints() == maxSugar;
//    });
//    maxValuedPlants.shrink_to_fit();
//    size_t size = maxValuedPlants.size();
//    if(size > 1)
//        return maxValuedPlants[ParametersSet::getRandomInt() % size];

//    return p;
//}


//void Herbivorous::eat(Being* b)
//{
//    Plant* p = static_cast<Plant*>(b);
//    //check whether on your place there is plant
////    this->saturationRate = 100.0f;
//    p->setHitPoints(0);
//    //if not, move to random place
//    move();
//}


