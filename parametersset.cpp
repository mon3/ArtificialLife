#include "parametersset.h"


int ParametersSet::getGridSize() const
{
    return _gridSize;
}

void ParametersSet::setSeason(Season newSeason)
{
    season = newSeason;
}

Season ParametersSet::getSeason()
{
    return season;
}


