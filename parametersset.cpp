#include "parametersset.h"


int ParametersSet::getGridSize() const
{
    return gridSize;
}

void ParametersSet::setSeason(Season newSeason)
{
    season = newSeason;
}

Season ParametersSet::getSeason()
{
    return season;
}
