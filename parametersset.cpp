#include "parametersset.h"
#include "beingwindow.h"

ParametersSet* ParametersSet::instance = nullptr;
int ParametersSet::BEING_WIDTH  = 25;

ParametersSet::ParametersSet(int gridSize)
    :  _gridSize(gridSize)
{
    BEING_WIDTH = (SCENE_WIDTH / _gridSize) >> 1;
    magic_offset = BEING_WIDTH >> 1;

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

    maxFoodCapacity = 20.0f;

    // instatiate lambda's
    checkCoordinate = [&] (int x, int y) -> bool
    {
        return (x >= 0 && y >= 0 && x < _gridSize && y < _gridSize);
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
    qDebug() << "removed";
}

int ParametersSet::getMaxPlantHp() const
{
    return MAX_PLANT_HP_LEVEL;
}

int ParametersSet::getStartHungerLevel() const
{
    return startHungerLevel;
}




vector<Plant*> ParametersSet::getAdjacentBeings(int logX, int logY, const int reach) const
{
    vector<Plant*> result;

    int checkX, checkY;

    //pushing to vector every being within animal reach
    //TODO: add comment to lookup section
    for(int i = 1; i <= reach; ++i) {
        if(i > _gridSize) break;
        for(int j = 0; j < 4; ++j) {
            checkX = logX + i * getColMod(j);
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


// don't like it, refactor
void ParametersSet::addBeing(Being *b)
{
    const int x = b->getLogX(),
              y = b->getLogY();
    //throw an exception?
    Animal* a;
    if((a = qobject_cast<Animal*>(b)) != 0)
        animalsOnBoard[x][y] = a;
    else
        plantsOnBoard[x][y] = qobject_cast<Plant*>(b);
    mapPosition(b);
}





void ParametersSet::mapPosition(Being *b)
{
    b->setPos((b->getLogX() * SCENE_WIDTH) / _gridSize + magic_offset,
              (b->getLogY() * SCENE_WIDTH) / _gridSize + magic_offset);
}

bool ParametersSet::isFreeCell(int x, int y)
{
    // TODO: throw exception instead
    if(!checkCoordinate(x, y))
        return false;

    return animalsOnBoard[x][y] == nullptr;
}

void ParametersSet::updateBeing(Being *b, const int oldX, const int oldY)
{
    const int x = b->getLogX(),
              y = b->getLogY();
    Animal* a = qobject_cast<Animal*>(b);
    if(a != 0)
    {
        animalsOnBoard[oldX][oldY] = nullptr;
        animalsOnBoard[x][y] = a;
    }
    mapPosition(b);
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


