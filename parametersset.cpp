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

    //very ugly; refactor later; use  c table instead?
    for(vector<Animal* >& vec : animalsOnBoard) {
        vec.resize(gridSize);
        vec = vector<Animal*>(gridSize, nullptr);
    }

    for(vector<Plant* >& vec : plantsOnBoard)
    {
        vec.resize(gridSize);
        vec = vector<Plant*>(gridSize, nullptr);

    }

    checkCoordinate = [&] (int x, int y) -> bool
    {
        return (x >= 0 && y >= 0 && x < _gridSize && y < _gridSize);
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

int ParametersSet::getPlantGrowbackLevel() const
{
    
    
    return plantGrowbackLevel;
}

void ParametersSet::removeBeing(Plant *)
{
    //nothing happens?
}

void ParametersSet::removeBeing(Animal * a)
{
    // remove from game board
    animalsOnBoard[a->getLogX()][a->getLogY()] = nullptr;
    a->scene()->removeItem(a);
    delete a;
}

int ParametersSet::getMaxPlantHp() const
{
    return MAX_PLANT_HP_LEVEL;
}

float ParametersSet::getStartHungerLevel() const
{
    return startHungerLevel;
}




vector<Plant*> ParametersSet::getAdjacentBeings(const Animal * a) const
{
    vector<Plant*> result;
    int logX = a->getLogX(), logY = a->getLogY()
       ,eveSight = a->getEveSight();
    int checkX, checkY;

    //pushing to vector every being within animal evesight
    //TODO: add comment to lookup section
    for(int i = 1; i <= eveSight; ++i) {
        if(i > _gridSize) break;
        for(int j = 0; j < 4; ++j) {
            checkX = logX + i * getColMod(j);
            checkY = logY + i * getRowMod(j);
            //add optimalization, for ev > grsize
            if(checkCoordinate(checkX, checkY)
                && plantsOnBoard[checkX][checkY] != nullptr
                && animalsOnBoard[checkX][checkY] == nullptr)
                result.push_back(plantsOnBoard[checkX][checkY]);
        }
    }

    if(plantsOnBoard[logX][logY] != nullptr)
        result.push_back(plantsOnBoard[logX][logY]);
    return result;
}


// don't like it, refactor
void ParametersSet::addBeing(Animal *a)
{
    int x = a->getLogX(),
        y = a->getLogY();
    animalsOnBoard[x][y] = a;

}

void ParametersSet::addBeing(Plant *p)
{
    plantsOnBoard[p->getLogX()][p->getLogY()] = p;
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


