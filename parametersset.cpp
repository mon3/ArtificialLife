#include "parametersset.h"
#include "beingwindow.h"
int ParametersSet::BEING_WIDTH = 40;

ParametersSet* ParametersSet::instance = nullptr;


ParametersSet::ParametersSet(int gridSize)
    : _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / gridSize) / 1.5;
    qDebug() << "grid size = " << gridSize ;
    qDebug() << "being_width = " << BEING_WIDTH;
    window = QSharedPointer<BeingWindow>(new BeingWindow);

    //instatiation of board
    animalsOnBoard = vector< vector<Animal* > >(gridSize, vector<Animal*>(gridSize));
    plantsOnBoard  = vector< vector<Plant* > >(gridSize, vector<Plant*>(gridSize));

    checkCoordinate = [&] (int x, int y) -> bool
    {
        return (x >= 0 && y <= 0 && x < _gridSize && y < _gridSize);
    };

    // TODO: ask to explain
    getRowMod = [](int x) -> int
    {
        return (x & 1) > 0 ? 0 : x - 1;
    };

    // TODO: ask to explaint
    getColMod = [](int x) -> int
    {
        return (x & 1) == 0 ? 0 : 2 - x;
    };
}

int ParametersSet::getPlantGrowbackLevel() const
{
    return plantGrowbackLevel;
}

float ParametersSet::getStartHungerLevel() const
{
    return startHungerLevel;
}


vector<Plant *> ParametersSet::getAdjacentPlants(Animal * a) const
{
    vector<Plant*> result;
    int logX = a->getLogX(), logY = a->getLogY()
       ,eyeSight = a->getEyeSight();
    int checkX, checkY;

    //pushing to vector every being within animal evesight
    //TODO: add comment to lookup section
    for(int i = 1; i <= eyeSight; ++i) {
        for(int j = 0; j < 3; ++j) {
            checkX = logX + i * getRowMod(j);
            checkY = logY + i * getRowMod(j);
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

vector<Herbivorous *> ParametersSet::getAdjacentHerbivorous(Animal* a) const
{
    vector<Herbivorous*> result;
    int logX = a->getLogX(), logY = a->getLogY()
       ,eveSight = a->getEyeSight();
    int checkX, checkY;
    for(int i = 1; i <= eveSight; ++i)
        for(int j = 0; j < 3; ++j) {
            checkX = logX + i * getRowMod(j);
            checkY = logY + i * getRowMod(j);
            if(checkCoordinate(checkX, checkY)) {
                Herbivorous* h =  qobject_cast<Herbivorous*>(animalsOnBoard[checkX][checkY]);
                if(h != 0)
                    result.push_back(h);
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


