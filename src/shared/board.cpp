#include "board.h"
#include "src/sugarscape/herbivorous.h"
#include "src/sugarscape/predator.h"
Board* Board::instance = nullptr;

Board::Board(const int gridSize_) : gridSize(gridSize_)
{
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


    // instatiate lambda's
    checkCoordinate = [&] (int x, int y) -> bool
    {
        return (x >= 0 && y >= 0 && x < gridSize && y < gridSize);
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

Board* Board::getInstance(const int gridSize_)
{
    if(instance == nullptr)
        instance = new Board(gridSize_);
    return instance;
}

Populations Board::getCurrentPopulation()
{
    QVector<std::shared_ptr<Animal>> herbPop;
    QVector<std::shared_ptr<Animal>> predPop;

    std::for_each(animalsOnBoard.begin(), animalsOnBoard.end(), [&](const std::vector<Animal*>& vec) -> void {
        std::for_each(std::begin(vec), std::end(vec), [&](Animal* a) -> void {
            Herbivorous* h = qobject_cast<Herbivorous*>(a);
            if(h != 0)
                herbPop.push_back(std::shared_ptr<Animal>(h));
            else
                predPop.push_back(std::shared_ptr<Predator>(qobject_cast<Predator*>(a)));
        });
    });

    return std::make_tuple(herbPop, predPop);
}

void Board::setCurrentPopulationOnBoard(const Populations &pop)
{
    const QVector<std::shared_ptr<Animal>>& herbPop = std::get<0>(pop);
    const QVector<std::shared_ptr<Animal>>& predPop = std::get<1>(pop);
    // make a template
    std::for_each(std::begin(herbPop), std::end(herbPop), [&](const std::shared_ptr<Animal>& h) -> void{
        Herbivorous* h_ = static_cast<Herbivorous*>(h.get());
        const int x = h_->getLogX(), y = h_->getLogY();
        if(animalsOnBoard[x][y] == nullptr)
            animalsOnBoard[x][y] = h_;
    });

    std::for_each(std::begin(predPop), std::end(predPop), [&](const std::shared_ptr<Animal>& p) -> void{
        Predator* h_ = static_cast<Predator*>(p.get());
        const int x = h_->getLogX(), y = h_->getLogY();
        if(animalsOnBoard[x][y] == nullptr)
            animalsOnBoard[x][y] = h_;
    });
}

std::vector<Plant *> Board::getAdjacentBeings(int logX, int logY, const int reach) const
{
    std::vector<Plant*> result;

    int checkX, checkY;

    //pushing to vector every being within animal reach
    //TODO: add comment to lookup section
    for(int i = 1; i <= reach; ++i) {
        if(i > gridSize) break;
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

void Board::addBeing(Being *b)
{
    const int x = b->getLogX(),
              y = b->getLogY();
    //throw an exception?
    Animal* a;
    if((a = qobject_cast<Animal*>(b)) != 0)
        animalsOnBoard[x][y] = a;
    else
        plantsOnBoard[x][y] = qobject_cast<Plant*>(b);
}

void Board::removeBeing(Animal *a)
{
    // remove from game board
    animalsOnBoard[a->getLogX()][a->getLogY()] = nullptr;
}

bool Board::isFreeCell(int x, int y)
{
    // TODO: throw exception instead
    if(!checkCoordinate(x, y))
        return false;

    return animalsOnBoard[x][y] == nullptr;
}

void Board::updateBeing(Being *b, const int oldX, const int oldY)
{
    const int x = b->getLogX(),
              y = b->getLogY();
    Animal* a = qobject_cast<Animal*>(b);
    if(a != 0)
    {
        animalsOnBoard[oldX][oldY] = nullptr;
        animalsOnBoard[x][y] = a;
    }
    //mapPosition(b);
}

Point Board::beingsInterpolation(const Being *a, const Being *b, const float &coeff)
{
    const int xA = a->getLogX(),
              xB = b->getLogX();
    const int yA = a->getLogY(),
              yB = b->getLogY();
    const bool equalX = xA == xB;
    const bool equalY = yA == yB;
    float x = xA, y = yB;

    // make correction due to float precision?
    if (equalX)
        y = yA * coeff + yB * (1 - coeff);
    if (equalY)
        x = xA * coeff + xB * (1 - coeff);


    //get adjacent free point
    // TODO: still possible endless loop
    for(int i =1; !isFreeCell(x, y); ++i)
        for(int j =0; j < 4; ++j)
        {
            int tempX = x + i * getColMod(j);
            int tempY = y + i * getRowMod(j);
            if(isFreeCell(tempX, tempY))
                return Point(tempX, tempY);
        }

    return Point(x, y);
}


void Board::visit(Plant *)
{

}

void Board::visit(Predator *p)
{
    removeBeing(p);
}

void Board::visit(Herbivorous *h)
{
    removeBeing(h);
}
