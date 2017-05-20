#include "animal.h"



void Animal::action()
{
//    if(activity == Activity::DEAD)
//        return;

//    //else, look for a site with bigger "sugar" value
//    Being* prey = hunt();

//    //if there is a prey to hunt, go there and collect resources from site,
//    if(prey != nullptr) {
//        move(prey->getLogX(), prey->getLogY());
//        eat(prey);
//    }
//    else // if no food, go to random adjacent place
//        move();
//    //for simplicity, assume that no exaustion is involved
//    saturationRate -= metabolism;

//    //animal is dead
//    if(saturationRate < 0.0f) {
//        activity = Activity::DEAD;
//        return;
//    }
}

void Animal::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Pressed!";
    emit callWindow(this);

}

void Animal::move(int x, int y )
{
    if(x == UNKNOWN_LOCATION || y == UNKNOWN_LOCATION)
    {
        //todo: check neighbours
        const int gridSize = ParametersSet::getInstance()->getGridSize();
        int addVal = (ParametersSet::getRandomInt() % 3) - 1;
        this->setLogX(this->getLogX() + addVal);
        addVal = (ParametersSet::getRandomInt() % 3) - 1;
        this->setLogY(this->getLogY() + addVal);
        qDebug() << "isSet: " << this->getLogX() << " y: " << this->getLogY() << endl;
    } else
    {
        this->setLogX(x);
        this->setLogY(y);
    }

}

void Animal::setEyeSight(int value)
{
    eyeSight = value;
}

int Animal::getEyeSight() const
{
    return eyeSight;
}

void Animal::setAge(int value)
{
    age = value;
}

int Animal::getAge() const
{
    return age;
}

void Animal::setGeneration(int value)
{
    generation = value;
}

int Animal::getGeneration() const
{
    return generation;
}

void Animal::setFoodCapacity(int value)
{
    foodCapacity = value;
}

int Animal::getFoodCapacity() const
{
    return foodCapacity;
}

void Animal::setSpeed(int value)
{
    // the number of frames the animal can jump over during 1 iteration
    speed = value;
}

int Animal::getSpeed() const
{
    return speed;
}

void Animal::setMetabolism(int value)
{
    metabolism = value;
}

int Animal::getMetabolism() const
{
    return metabolism;
}

void Animal::setExhaustionLevel(int value)
{
    exhaustionLevel = value;
}

int Animal::getExhaustionLevel() const
{
    return exhaustionLevel;
}

void Animal::setSaturationRate(int value)
{
    saturationRate = value;
}

int Animal::getSaturationRate() const
{
    return saturationRate;
}

void Animal::setStdDevs(QVector<double> vals)
{
    stdDevs = vals;
}

QVector<double> Animal::getStdDevs() const
{
    return stdDevs;
}

// TODO:: verify if &vals is needed
void Animal::setFeaturesEA(QVector<int>& vals, Beings beingType)
{
    vals[0] = ((vals.at(0)<=ParametersSet::minEyeSight) ? ParametersSet::minEyeSight: vals.at(0));
    vals[0] = ((vals.at(0)>=ParametersSet::maxEyeSight) ? ParametersSet::maxEyeSight: vals.at(0));

    vals[2] = ((vals.at(2)<=ParametersSet::minHitPoints) ? ParametersSet::minHitPoints: vals.at(2));
    vals[2] = ((vals.at(2)>=ParametersSet::maxHitPoints) ? ParametersSet::maxHitPoints: vals.at(2));

    vals[5] = ((vals.at(5)<=ParametersSet::minExhaustionLevel) ? ParametersSet::minExhaustionLevel: vals.at(5));
    vals[5] = ((vals.at(5)>=ParametersSet::maxExhaustionLevel) ? ParametersSet::maxExhaustionLevel: vals.at(5));

    if (beingType == Beings::PREDATOR)
    {
        vals[1] = ((vals.at(1)<=ParametersSet::minPredatorSpeed) ? ParametersSet::minPredatorSpeed: vals.at(1));
        vals[1] = ((vals.at(1)>=ParametersSet::maxPredatorSpeed) ? ParametersSet::maxPredatorSpeed: vals.at(1));

        vals[3] = ((vals.at(3)<=ParametersSet::minPredatorMetabolism) ? ParametersSet::minPredatorMetabolism: vals.at(3));
        vals[3] = ((vals.at(3)>=ParametersSet::maxPredatorMetabolism) ? ParametersSet::maxPredatorMetabolism: vals.at(3));

        vals[4] = ((vals.at(4)<=ParametersSet::minPredatorFoodCapacity) ? ParametersSet::minPredatorFoodCapacity: vals.at(4));
        vals[4] = ((vals.at(4)>=ParametersSet::maxPredatorFoodCapacity) ? ParametersSet::maxPredatorFoodCapacity: vals.at(4));

    }
    else if (beingType == Beings::HERBIVOROUS)
    {
        vals[1] = ((vals.at(1)<=ParametersSet::minHerbivorousSpeed) ? ParametersSet::minHerbivorousSpeed: vals.at(1));
        vals[1] = ((vals.at(1)>=ParametersSet::maxHerbivorousSpeed) ? ParametersSet::maxHerbivorousSpeed: vals.at(1));

        vals[3] = ((vals.at(3)<=ParametersSet::minHerbivorousMetabolism) ? ParametersSet::minHerbivorousMetabolism: vals.at(3));
        vals[3] = ((vals.at(3)>=ParametersSet::maxHerbivorousMetabolism) ? ParametersSet::maxHerbivorousMetabolism: vals.at(3));

        vals[4] = ((vals.at(4)<=ParametersSet::minHerbivorousFoodCapacity) ? ParametersSet::minHerbivorousFoodCapacity: vals.at(4));
        vals[4] = ((vals.at(4)>=ParametersSet::maxHerbivorousFoodCapacity) ? ParametersSet::maxHerbivorousFoodCapacity: vals.at(4));
    }
    else
    {
        qDebug() << "WRONG BEING TYPE PASSED AS VALUE! ";
    }

    featuresEA = vals;
}

void Animal::setFeaturesEA(QVector<int> vals)
{
    featuresEA = vals;
}

QVector<int> Animal::getFeaturesEA() const
{
    return featuresEA;
}


void Animal::displayFeatures() const
{
    for (const int& feature : featuresEA) // access by const reference
    {
        qDebug() <<"Feature: " << feature;
    }
    qDebug() << '\n';
}

void Animal::displayStd() const
{
    for (const double& std : stdDevs) // access by const reference
    {
        qDebug() <<"Sigma: " << std;
    }
    qDebug() << '\n';
}
