#include "herbivorous.h"


Herbivorous::Herbivorous(int logX, int logY): Animal(logX, logY)
{
    QVector<int> randFeatures;
    randFeatures.push_back(static_cast<int>(rand()*ParametersSet::maxEyeSight));
    randFeatures.push_back(static_cast<int>(rand()*ParametersSet::maxHerbivorousSpeed));
    randFeatures.push_back(static_cast<int>(1.0*ParametersSet::maxHitPoints));
    randFeatures.push_back(static_cast<int>(rand()*ParametersSet::maxHerbivorousMetabolism));
    randFeatures.push_back(static_cast<int>(rand()*ParametersSet::maxHerbivorousFoodCapacity));
    randFeatures.push_back(static_cast<int>(1.0*ParametersSet::minExhaustionLevel));

    setFeaturesForEA(randFeatures);

}




Herbivorous::Herbivorous(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity, int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs):Animal(x,y)
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
    setFeaturesForEA(features);
    setStdDevs(stdDevs);
}


void Herbivorous::setFeaturesForEA(QVector<int>& vals)
{
    vals[0] = ((vals.at(0)<=ParametersSet::minEyeSight) ? ParametersSet::minEyeSight: vals.at(0));
    vals[0] = ((vals.at(0)>=ParametersSet::maxEyeSight) ? ParametersSet::maxEyeSight: vals.at(0));

    vals[1] = ((vals.at(1)<=ParametersSet::minHerbivorousSpeed) ? ParametersSet::minHerbivorousSpeed: vals.at(1));
    vals[1] = ((vals.at(1)>=ParametersSet::maxHerbivorousSpeed) ? ParametersSet::maxHerbivorousSpeed: vals.at(1));

    vals[2] = ((vals.at(2)<=ParametersSet::minHitPoints) ? ParametersSet::minHitPoints: vals.at(2));
    vals[2] = ((vals.at(2)>=ParametersSet::maxHitPoints) ? ParametersSet::maxHitPoints: vals.at(2));

    vals[3] = ((vals.at(3)<=ParametersSet::minHerbivorousMetabolism) ? ParametersSet::minHerbivorousMetabolism: vals.at(3));
    vals[3] = ((vals.at(3)>=ParametersSet::maxHerbivorousMetabolism) ? ParametersSet::maxHerbivorousMetabolism: vals.at(3));

    vals[4] = ((vals.at(4)<=ParametersSet::minHerbivorousFoodCapacity) ? ParametersSet::minHerbivorousFoodCapacity: vals.at(4));
    vals[4] = ((vals.at(4)>=ParametersSet::maxHerbivorousFoodCapacity) ? ParametersSet::maxHerbivorousFoodCapacity: vals.at(4));

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


QVector<int> Herbivorous::featuresToChromosome()
{
    QVector<int> chromosome;
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[0], ParametersSet::minEyeSight, ParametersSet::maxEyeSight));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[1], ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[2], ParametersSet::minHitPoints, ParametersSet::maxHitPoints));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[3], ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[4], ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity));
    chromosome.push_back(normalizeFeature(this->getFeaturesEA()[5], ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel));

    return chromosome;
}



//Being* Herbivorous::hunt()
Being* Herbivorous::hunt()
{
    vector<Plant*> vec = ParametersSet::getInstance()->getAdjacentBeings(this->getLogX(), this->getLogY(), getSpeed());
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
    const int size = maxValuedPlants.size();
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
