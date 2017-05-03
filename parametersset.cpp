#include "parametersset.h"
int ParametersSet::BEING_WIDTH = 40;

ParametersSet::ParametersSet(int gridSize)
    : _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / gridSize) / 1.5;
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

Season ParametersSet::getSeason()
{
    return season;
}


