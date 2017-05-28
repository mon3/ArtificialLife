#include "animal.h"

const function<int(int)> Animal::direction = [](const int& delta) -> int
{
    // which means, we should not move in this dimension
    if(delta == 0) return 0;

    // if delta > 0, means that we should move to the right || down,
    // opposite in reverse
    return delta > 0 ? 1 : -1;
};


void Animal::action()
{

    if(activity == Activity::DEAD) {
        return ParametersSet::getInstance()->removeBeing(this);
    }

    int oldX = this->getLogX(),
        oldY = this->getLogY();

    ParametersSet* set = ParametersSet::getInstance();

    enemiesHandlingRoutine();

    if(activity != RUNNNING_AWAY)
    {
        //hunting process, if hungry
        const float hungerLevel = set->getStartHungerLevel();
        if(saturationRate < hungerLevel) {

            activity = HUNTING;
            huntRoutine();

            //after hunting, unless animal is satisfied, consume inner reserve
            if(saturationRate < hungerLevel && foodCapacity > 0)
            {
                foodConsumptionRoutine(set);
            }
        }
        else
        {
            activity = IDLE;
            move();
        }

    }

    // parameters correction section

    //for each turn, saturation rate decreased
    saturationRate -= metabolism;

    // TODO: add exaustion level based on current state
    exaustionLevelHandlingRoutine(set);

    //animal is dead
    // TODO: complete with min/max values
    if(saturationRate < 0) {
        activity = Activity::DEAD;
        return;
    }
    else
        set->updateBeing(this, oldX, oldY);
}

void Animal::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit callWindow(this);
}

void Animal::foodConsumptionRule(int &foodValue)
{
    ParametersSet* set = ParametersSet::getInstance();
    float currentSaturationRate = this->getSaturationRate();
    // TODO: set max saturation value
    if(currentSaturationRate + foodValue < 100.0f)
    {
        // if a whole plant is not enough to satisfy hunger, just eat it all
        this->setSaturationRate(currentSaturationRate + foodValue);
        foodValue = 0;
    }
    else
    {
        int delta = 100.0f - currentSaturationRate;
        this->setSaturationRate(100.0f);
        foodValue -= delta;

        int currentFoodCapacity = this->getFoodCapacity();

        // try to take as many plants as you can
        const int maxFoodCapacity = set->getMaxFoodCapacity();
        if(currentFoodCapacity + foodValue < maxFoodCapacity)
        {
            this->setFoodCapacity(currentFoodCapacity + foodValue);
            foodValue = 0;
        }
        else
        {
            // if not, fill up your food cap
            foodValue -= set->getMaxFoodCapacity() - currentFoodCapacity;
            this->setFoodCapacity(maxFoodCapacity);
        }

    }
}

void Animal::move(int x, int y )
{
    auto set = ParametersSet::getInstance();
    //move to random free location, within being reach
    if(x == UNKNOWN_LOCATION || y == UNKNOWN_LOCATION)
    {
        // if being is idle
        int goalX, goalY, addVal;
        if(activity == IDLE)
        {
            moveClose(this->getLogX() + ParametersSet::getRandomInt(-1, 2),
                      this->getLogY() + ParametersSet::getRandomInt(-1, 2));
        }
        else if (activity == HUNTING)
        {
            const int addVal = speed;
            goalX = addVal * direction(ParametersSet::getRandomInt(-1, 2));
            goalY = addVal * direction(ParametersSet::getRandomInt(-1, 2));
            moveClose(goalX, goalY);
        }
    } else
    {
        this->setLogX(x);
        this->setLogY(y);
    }
}

void Animal::moveClose(int goalX, int goalY)
{
    ParametersSet* set = ParametersSet::getInstance();

    // direction of moving 1, 0, -1
    int directionVector[2] = {direction(goalX - this->getLogX()), direction(goalY - this->getLogY())};

    //move to the closest free cell
    if(directionVector[0] != 0 || directionVector[1] != 0)
        while(!set->isFreeCell(goalX, goalY) && set->checkCoordinate(goalX, goalY))
        {
            goalX -= directionVector[0];
            goalY += directionVector[1];
        }
    move(goalX, goalY);
}

void Animal::runFrom(const vector<Animal *>& enemies)
{
    // we should find the safest place to run away
    int safeX = getLogX(),
        safeY = getLogY();


    // being can see enemies only in four directions, we should
    // find an optimal position to move(assuming that there are up to four enemies)
    int minDistance = numeric_limits<int>::max();
    const Animal* enemy = nullptr;
    // find the closest enemy
    for(const Animal* a : enemies)
    {
        int temp = abs(a->getLogX() - safeX + a->getLogY() - safeY);
        if(temp < minDistance)
        {
            minDistance = temp;
            enemy = a;
        }
    }
    ParametersSet* set = ParametersSet::getInstance();
    // try to run from him, for it's most likely he won't notice
    // TODO: add handler functions
    int modifier = set->getRandomInt(0, 2) > 0 ? 1 : -1;
    if(safeX == enemy->getLogX())
    {
        if(!set->checkCoordinate(safeX, safeY + modifier))
            modifier = -modifier;
        const int inc = modifier;
        while(!set->isFreeCell(safeX, safeY + modifier))
            modifier += inc;
        move(safeX, safeY  + modifier);
    }
    else
    {
        if(!set->checkCoordinate(safeX + modifier, safeY))
            modifier = -modifier;
        const int inc = modifier;
        while(!set->isFreeCell(safeX + modifier, safeY))
            modifier += inc;
        move(safeX  + modifier, safeY);
    }
}

void Animal::huntRoutine()
{
    //if there not, hunt
    Being* prey = hunt();

    //if there is a prey to hunt, go there and collect resources from site,
    if(prey != nullptr) {
        int goalX = prey->getLogX(),
            goalY = prey->getLogY();

        //unless you can reach prey in one turn, get as close as you could
        if(speed < eveSight) {

            int directionVector[2] = {direction(goalX - this->getLogX()), direction(goalY - this->getLogY())};
            // if direcVec > 0, means we should move to the right, so decrease goalX, increase goalY
            // do reverse in opposite
            goalX = this->getLogX() + directionVector[0] * speed;
            goalY = this->getLogY() + directionVector[1] * speed;
            moveClose(goalX, goalY);
        } else {
            eat(prey);
            move(goalX, goalY);
        }

    } else {
        // if no food, go to random adjacent place,
        // we assume, that this place should be as far, as being could reach, to increase chance of finding food
        move();
    }
}

void Animal::enemiesHandlingRoutine()
{
    // we assume, that these are most dangerous for being
    vector<Animal*> dangerousEnemies = findEnemies();
    if(!dangerousEnemies.empty()) {
        activity = RUNNNING_AWAY;
        runFrom(dangerousEnemies);
    }

}

void Animal::foodConsumptionRoutine(ParametersSet *set)
{
    // consume food from inner reserves, as much
    // as you can in one turn

    // first, determine how much food you must eat

    // second, determine how much food you can eat

    //if >, cons. all food

    // else, cons. delta

}

void Animal::exaustionLevelHandlingRoutine(ParametersSet *set)
{
    // based on current activity, inc / dec exaustion level
    // TODO: complete after merging
    switch (activity) {
    case Animal::HUNTING:
        // exaustion increased
        break;
    case Animal::IDLE:
        // exaustion decreased
        break;
    case Animal::RUNNNING_AWAY:
        //exaustionLevel increased high
        break;
    default:
        break;
    };
}

Animal::Activity Animal::getActivity() const
{
    return activity;
}

int Animal::getSpeed() const
{
    return speed;
}

void Animal::setSpeed(int value)
{
    speed = value;
}

int Animal::getMetabolism() const
{
    return metabolism;
}

int Animal::getFoodCapacity() const
{
    return foodCapacity;
}

void Animal::setFoodCapacity(int value)
{
    foodCapacity = value;
}

int Animal::getSaturationRate() const
{
    return saturationRate;
}

void Animal::setSaturationRate(int value)
{
    saturationRate = value;
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
    setEyeSight(vals[0]);
    setSpeed(vals[1]);
    setHitPoints(vals[2]);
    setMetabolism(vals[3]);
    setFoodCapacity(vals[4]);
    setExhaustionLevel(vals[5]);
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
