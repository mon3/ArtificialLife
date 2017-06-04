#include "src/shared/parametersset.h"
#include "src/grid/beingwindow.h"

ParametersSet* ParametersSet::instance = nullptr;
int ParametersSet::BEING_WIDTH  = 25;

ParametersSet::ParametersSet(int gridSize)
    :  _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / _gridSize) >> 1;

    window = QSharedPointer<BeingWindow>(new BeingWindow);

    //instatiation of board
    animalsOnBoard = std::vector< std::vector<Animal* > >(gridSize, std::vector<Animal*>(gridSize));
    plantsOnBoard  = std::vector< std::vector<Plant* > >(gridSize, std::vector<Plant*>(gridSize));

    //very ugly; refactor later; use  c table instead?
    for(std::vector<Animal* >& vec : animalsOnBoard) {
        vec.resize(gridSize);
        vec = std::vector<Animal*>(gridSize, nullptr);
    }

    for(std::vector<Plant* >& vec : plantsOnBoard)
    {
        vec.resize(gridSize);
        vec = std::vector<Plant*>(gridSize, nullptr);
    }

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

int ParametersSet::getPlantGrowbackLevel() const
{
    return plantGrowbackLevel;
}


int ParametersSet::getMaxPlantHp() const
{
    return MAX_PLANT_HP_LEVEL;
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

void ParametersSet::setSeason(Season newSeason)
{
    season = newSeason;
}



int ParametersSet::getRandomInt(const int& min, const int& max)
{
    return (rand() % (max - min)) + min;
}

void ParametersSet::callWindow(Being * b)
{
    if(!window->isVisible()) {
        window->initWindow(b);
        window->show();
    }

}

Season ParametersSet::getSeason()
{
    return season;
}


