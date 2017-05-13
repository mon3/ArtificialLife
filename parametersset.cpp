#include "parametersset.h"
#include "beingwindow.h"
int ParametersSet::BEING_WIDTH = 40;

ParametersSet* ParametersSet::instance = nullptr;


ParametersSet::ParametersSet(int gridSize)
    : _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / gridSize) / 1.5;
    window = QSharedPointer<BeingWindow>(new BeingWindow);

    //instatiation of board
    animalsOnBoard = vector< vector<Animal* > >(gridSize, vector<Animal*>(gridSize));
    plantsOnBoard  = vector< vector<Plant* > >(gridSize, vector<Plant*>(gridSize));

    checkCoordinate = [&] (int x, int y) -> bool
    {
        return (x >= 0 && y <= 0 && x < _gridSize && y < _gridSize);
    };

    getRowMod = [](int x) -> int
    {
        return (x & 1) > 0 ? 0 : x - 1;
    };

    getColMod = [](int x) -> int
    {
        return (x & 1) == 0 ? 0 : 2 - x;
    };
}

float ParametersSet::getStartHungerLevel() const
{
    return startHungerLevel;
}


vector<Being *> ParametersSet::getAdjacentHuntSubjects(Animal * a) const
{
    vector<Being*> result;
    int logX = a->getLogX(), logY = a->getLogY()
       ,eveSight = a->getEveSight();
    int checkX, checkY;

    //pushing to vector every being within animal evesight
    //TODO: add comment to lookup section
    for(int i = 1; i <= eveSight; ++i) {
        for(int j = 0; j < 3; ++j) {
            checkX = logX + i * getRowMod(j);
            checkY = logY + i * getRowMod(j);
            if(checkCoordinate(checkX, checkY)
                && animalsOnBoard[checkX][checkY] != nullptr)
                result.push_back(animalsOnBoard[checkX][checkY]);
        }
    }


    return result;
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


