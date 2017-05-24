#include "animal.h"

const function<int(int)> Animal::direction = [=](int delta) -> int
{
    // which means, we should not move in this dimension
    if(delta == 0) return 0;

    // if delta > 0, means that we should move to the right || down,
    // opposite in reverse
    return delta > 0 ? 1 : -1;
};


void Animal::action()
{
    if(activity == Activity::DEAD)
        return;

    ParametersSet* set = ParametersSet::getInstance();

    huntRoutine(set);

    //hunting process, if hungry
    const float hungerLevel = set->getStartHungerLevel();
    if(saturationRate < hungerLevel && activity != RUNNNING_AWAY) {
        activity = HUNTING;
        huntRoutine(set);
    }

    //after hunting, unless animal is satisfied, consume inner reserve
    if(saturationRate < hungerLevel && foodCapacity > 0)
    {
        float foodConsumption = set->getFoodConsumptionUnits();

    }
    // parameters correction

    //for simplicity, assume that no exaustion is involved
    saturationRate -= metabolism;

    // TODO: add exaustion level based on current state
    // & saturation rate

    //animal is dead
    if(saturationRate < 0.0f) {
        activity = Activity::DEAD;
        return;
    }
}

void Animal::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit callWindow(this);
}

void Animal::move(int x, int y )
{
    auto set = ParametersSet::getInstance();
    //move to random free location, within being reach


    if(x == UNKNOWN_LOCATION || y == UNKNOWN_LOCATION)
    {
        // first, check being activity, if hungry - go as far
        // as you could, else do not go far away
        //todo: check neighbours
        const int gridSize = set->getGridSize();


        int addVal = (ParametersSet::getRandomInt() % 3) - 1;
        this->setLogX(this->getLogX() + addVal);
        addVal = (ParametersSet::getRandomInt() % 3) - 1;
        this->setLogY(this->getLogY() + addVal);
    } else
    {
        this->setLogX(x);
        this->setLogY(y);
    }

}

void Animal::huntRoutine(ParametersSet* set)
{
    //if there not, hunt
    Being* prey = hunt();

    //if there is a prey to hunt, go there and collect resources from site,
    if(prey != nullptr) {
        int goalX = prey->getLogX(),
            goalY = prey->getLogY();

        //unless you can reach prey in one turn, get as close as you could
        if(speed < eveSight) {
            // direction of moving 1, 0, -1
            int directionVector[2] = {direction(goalX - this->getLogX()), direction(goalY - this->getLogY())};

            // if direcVec > 0, means we should move to the right, so decrease goalX, increase goalY
            // do reverse in opposite
            goalX -= directionVector[0] * speed;
            goalY += directionVector[1] * speed;

            //move to the closest free cell
            while(!set->isFreeCell(goalX, goalY))
            {
                goalX -= directionVector[0];
                goalY += directionVector[1];
            }
            move(goalX, goalY);
        } else {
            move(goalX, goalY);
            eat(prey);
        }
    } else {
        // if no food, go to random adjacent place,
        // we assume, that this place should be as far, as being could reach, to increase chance of finding food
        move();
    }
}

void Animal::enemiesHandlingRoutine()
{

}

int Animal::getSpeed() const
{
    return speed;
}

void Animal::setSpeed(int value)
{
    speed = value;
}

float Animal::getMetabolism() const
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

float Animal::getSaturationRate() const
{
    return saturationRate;
}

void Animal::setSaturationRate(float value)
{
    saturationRate = value;
}

int Animal::getEveSight() const
{
    return eveSight;
}

