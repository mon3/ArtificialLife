#include "predator.h"

Predator::Predator(int logX, int logY): Animal(logX, logY)
{
    QVector<int> randFeatures;
    randFeatures.push_back(static_cast<int>((this->randomDouble(0.1, 1.0))*ParametersSet::maxEyeSight));
    randFeatures.push_back(static_cast<int>((this->randomDouble(0.1, 1.0))*ParametersSet::maxPredatorSpeed));
    randFeatures.push_back(static_cast<int>(1.0*ParametersSet::maxHitPoints));
    randFeatures.push_back(static_cast<int>((this->randomDouble(0.1, 1.0))*ParametersSet::maxPredatorMetabolism));
    randFeatures.push_back(static_cast<int>((this->randomDouble(0.1, 1.0))*ParametersSet::maxPredatorFoodCapacity));
    randFeatures.push_back(static_cast<int>(1.0*ParametersSet::minExhaustionLevel));

    setFeaturesForEA(randFeatures);

}


Predator::Predator(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity, int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs):Animal(x,y)
{
    QVector<int> featuresVec = this->featuresToVectorEA(eyeSight, speed, hitPoints, metabolism, foodCapacity, exhaustionLevel);
    setFeaturesForEA(featuresVec);
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
    QVector<int> featuresVec = this->featuresToVectorEA(eyeSight, speed, hitPoints, metabolism, foodCapacity, exhaustionLevel);
    setFeaturesForEA(featuresVec);
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
    setFeaturesForEA(features);
    setStdDevs(stdDevs);
}
void Predator::setFeatureStdevs(FeatureStd Eye, FeatureStd Speed, FeatureStd HitPoints, FeatureStd Metabolism, FeatureStd FoodCapacity, FeatureStd ExhLevel)
{

    QVector<int> vals;
    vals.push_back(Eye.feature);
    vals.push_back(Speed.feature);
    vals.push_back(HitPoints.feature);
    vals.push_back(Metabolism.feature);
    vals.push_back(FoodCapacity.feature);
    vals.push_back(ExhLevel.feature);
    this->setFeaturesForEA(vals);

    QVector<double> stdDevs;
    stdDevs.push_back(Eye.stdDev);
    stdDevs.push_back(Speed.stdDev);
    stdDevs.push_back(HitPoints.stdDev);
    stdDevs.push_back(Metabolism.stdDev);
    stdDevs.push_back(FoodCapacity.stdDev);
    stdDevs.push_back(ExhLevel.stdDev);
    this->setStdDevs(stdDevs);
}



void Predator::setFeaturesForEA(QVector<int>& vals)
{
    vals[0] = ((vals.at(0)<=ParametersSet::minEyeSight) ? ParametersSet::minEyeSight: vals.at(0));
    vals[0] = ((vals.at(0)>=ParametersSet::maxEyeSight) ? ParametersSet::maxEyeSight: vals.at(0));

    vals[1] = ((vals.at(1)<=ParametersSet::minPredatorSpeed) ? ParametersSet::minPredatorSpeed: vals.at(1));
    vals[1] = ((vals.at(1)>=ParametersSet::maxPredatorSpeed) ? ParametersSet::maxPredatorSpeed: vals.at(1));

    vals[2] = ((vals.at(2)<=ParametersSet::minHitPoints) ? ParametersSet::minHitPoints: vals.at(2));
    vals[2] = ((vals.at(2)>=ParametersSet::maxHitPoints) ? ParametersSet::maxHitPoints: vals.at(2));

    vals[3] = ((vals.at(3)<=ParametersSet::minPredatorMetabolism) ? ParametersSet::minPredatorMetabolism: vals.at(3));
    vals[3] = ((vals.at(3)>=ParametersSet::maxPredatorMetabolism) ? ParametersSet::maxPredatorMetabolism: vals.at(3));

    vals[4] = ((vals.at(4)<=ParametersSet::minPredatorFoodCapacity) ? ParametersSet::minPredatorFoodCapacity: vals.at(4));
    vals[4] = ((vals.at(4)>=ParametersSet::maxPredatorFoodCapacity) ? ParametersSet::maxPredatorFoodCapacity: vals.at(4));

    vals[5] = ((vals.at(5)<=ParametersSet::minExhaustionLevel) ? ParametersSet::minExhaustionLevel: vals.at(5));
    vals[5] = ((vals.at(5)>=ParametersSet::maxExhaustionLevel) ? ParametersSet::maxExhaustionLevel: vals.at(5));

    this->setFeaturesEA(vals);
    setEyeSight(vals[0]);
    setSpeed(vals[1]);
    setHitPoints(vals[2]);
    setMetabolism(vals[3]);
    setFoodCapacity(vals[4]);
    setExhaustionLevel(vals[5]);
}





QVector<int> Predator::featuresToChromosome()
{
    QVector<int> chromosome;
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[0], ParametersSet::minEyeSight, ParametersSet::maxEyeSight));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[1], ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[2], ParametersSet::minHitPoints, ParametersSet::maxHitPoints));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[3], ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[4], ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[5], ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel));

    return chromosome;
}



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
    herb->setIsDead();
    qDebug() << "eaten!";
}


std::vector<Animal*> Predator::findEnemies()
{
    //does nothing
    return std::vector<Animal*>();
}

