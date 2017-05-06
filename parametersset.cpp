#include "parametersset.h"
#include "beingwindow.h"
int ParametersSet::BEING_WIDTH = 40;

ParametersSet::ParametersSet(int gridSize)
    : _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / gridSize) / 1.5;
    window = new BeingWindow();
}

ParametersSet *ParametersSet::getInstance(int gridSize = 0)
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

int ParametersSet::getRandomInt()
{
    return rand();
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


