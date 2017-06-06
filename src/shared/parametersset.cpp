#include "src/shared/parametersset.h"
#include "src/grid/beingwindow.h"

ParametersSet* ParametersSet::instance = nullptr;
int ParametersSet::BEING_WIDTH  = 25;

ParametersSet::ParametersSet(int gridSize)
    :  _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / _gridSize) >> 1;


    maxFoodCapacity = 20.0f;
}

float ParametersSet::getFoodConsumptionUnits() const
{
    return foodConsumptionUnits;
}

float ParametersSet::getMaxFoodCapacity() const
{
    return maxFoodCapacity;
}



int ParametersSet::getMaxPlantHp() const
{
    return MAX_PLANT_HP_LEVEL;
}

int ParametersSet::getPlantGrowbackLevel() const
{
    return plantGrowbackLevel;
}

int ParametersSet::getStartHungerLevel() const
{
    return startHungerLevel;
}



ParametersSet *ParametersSet::getInstance(int gridSize)
{
    if(instance == nullptr)
        instance = new ParametersSet(gridSize);

    return instance;
}

int ParametersSet::getGridSize() const
{
    return _gridSize;
}





int ParametersSet::getRandomInt(const int& min, const int& max)
{
    return (rand() % (max - min)) + min;
}






