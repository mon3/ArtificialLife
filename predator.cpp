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



Predator::Predator(int x, int y, ConstrainedEyeSight es, ConstrainedPredatorSpeed speed, ConstrainedHitPoints hp,
                   ConstrainedPredatorMetabolism metab, ConstrainedPredatorFoodCapcity fc, ConstrainedExhLevel exhLev,
                   QVector<double> stdDevs):Animal(x, y)
{

    setPredEyeSightConstr(es);
    setPredSpeedConstr(speed);
    setPredHitPointsConstr(hp);
    setPredMetabolismConstr(metab);
    setPredFoodCapacityConstr(fc);
    setPredExhLevel(exhLev);
    setStdDevs(stdDevs);
}

Being* Predator::hunt()
{
    return nullptr;
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
