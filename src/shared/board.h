#ifndef BOARD_H
#define BOARD_H
#include "src/sugarscape/animal.h"
#include "src/sugarscape/plant.h"

class Board
{
private:
    std::vector<std::vector<Plant*>> plantsOnBoard;
    std::vector<std::vector<Animal*>> animalsOnBoard;

    std::function<int(int)> getRowMod;
    std::function<int(int)> getColMod;
public:
    Board();

    template<typename T>
    std::vector<T> getAdjacentBeings(int logX, int logY, const int) const;

    std::vector<Plant*> getAdjacentBeings(int logX, int logY, const int) const;

    void addBeing(Being*);
    void removeBeing(Plant*);
    void removeBeing(Animal*);

    bool isFreeCell(int x, int y);
    std::function<bool(int, int)> checkCoordinate;
    void updateBeing(Being* b, const int oldX, const int oldY);
};

#endif // BOARD_H
