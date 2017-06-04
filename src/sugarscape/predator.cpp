#include "predator.h"

Predator::Predator(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity, int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs):Animal(x,y)
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

Predator::Predator(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism, int foodCapacity, int exhaustionLevel, QVector<double> stdDevs):Animal(x, y)
{
    setEyeSight(eyeSight);
    setSpeed(speed);
    setHitPoints(hitPoints);
    setMetabolism(metabolism);
    setFoodCapacity(foodCapacity);
    setExhaustionLevel(exhaustionLevel);
    setStdDevs(stdDevs);
}

Predator::Predator(int x, int y, QVector<int> features, QVector<double> stdDevs):Animal(x, y)
{

    setFeaturesEA(features, Beings::PREDATOR);
    setStdDevs(stdDevs);
}



//Predator::Predator(int x, int y, ConstrainedEyeSight es, ConstrainedPredatorSpeed speed, ConstrainedHitPoints hp,
//                   ConstrainedPredatorMetabolism metab, ConstrainedPredatorFoodCapcity fc, ConstrainedExhLevel exhLev,
//                   QVector<double> stdDevs):Animal(x, y)
//{

//    setPredEyeSightConstr(es);
//    setPredSpeedConstr(speed);
//    setPredHitPointsConstr(hp);
//    setPredMetabolismConstr(metab);
//    setPredFoodCapacityConstr(fc);
//    setPredExhLevel(exhLev);
//    setStdDevs(stdDevs);
//}

Being* Predator::hunt()
{
    qDebug() << "here1";
    std::vector<Herbivorous*> vec = Board::getInstance()->
            getAdjacentBeings<Herbivorous*>(this->getLogX(), this->getLogY(), this->getEyeSight());
    //no available plant at neighbourhood
    if(vec.empty()) {
        return nullptr;
    }

    //find most valuable plant
    Herbivorous* p = nullptr;
    int maxSugar = std::numeric_limits<int>::min();


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
    std::vector<Herbivorous*> maxValuedPlants;

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(maxValuedPlants), [&](Herbivorous* _p) -> bool {
       return _p->getHitPoints() == maxSugar;
    });

    maxValuedPlants.shrink_to_fit();

    //if there is several max positions, select one randomly
    const int  size = maxValuedPlants.size();
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
    // error
    Board::getInstance()->removeBeing(herb);
}


std::vector<Animal*> Predator::findEnemies()
{
    //does nothing
    return std::vector<Animal*>();
}


void Predator::setPredEyeSightConstr(ConstrainedEyeSight eyeSightConstr)
{
    eyeSightConstr_ = eyeSightConstr;
}
void Predator::setPredHitPointsConstr(ConstrainedHitPoints hitPointsConstr)
{
    hitPointsConstr_ = hitPointsConstr;
}

void Predator::setPredFoodCapacityConstr(ConstrainedPredatorFoodCapcity foodCapacityConstr)
{
    foodCapacityConstr_ = foodCapacityConstr;
}

void Predator::setPredMetabolismConstr(ConstrainedPredatorMetabolism metabolismConstr)
{
    metabolismConstr_ = metabolismConstr;
}

void Predator::setPredExhLevel(ConstrainedExhLevel exhLevelConstr)
{
    exhLevelConstr_ = exhLevelConstr;
}

void Predator::setPredSpeedConstr(ConstrainedPredatorSpeed speedConstr)
{
    speedConstr_ = speedConstr;
}


void Predator::accept(Visitor *v)
{
    v->visit(this);
}
