#ifndef BOARD_H
#define BOARD_H
#include "src/sugarscape/animal.h"
#include "src/sugarscape/plant.h"


typedef std::pair<int, int> Point;

/*!
 * \brief The Board class handles location of Beings
 *
 * Singleton; provides information about current game board
 *
 *  \ingroup shared
 */
class Board : public Visitor
{
private:
    std::vector<std::vector<Plant*>> plantsOnBoard; ///< current plants on board
    std::vector<std::vector<Animal*>> animalsOnBoard; ///< current animals on the board

    std::function<int(int)> getRowMod;
    std::function<int(int)> getColMod;
    const int gridSize;
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(int gridSize);
    static Board* instance;
public:
    static Board* getInstance(const int gridSize_ = -1);

    template<typename T>
    /*!
     * \brief getAdjacentBeings returns adjacent beings from specified place
     * \param logX, logY Defines point, from which we finding animals
     * \param reach How far from this point we are looking for food
     * \return Vector of beings from within reach
     */
    std::vector<T> getAdjacentBeings(int logX, int logY, const int reach) const;
    /*!
     * \brief getAdjacentBeings returns adjacent plants from specified place
     * \param logX, logY Defines point, from which we finding plants
     * \param reach How far from this point we are looking for food, including this point
     * \return Vector of plants from within reach
     */
    std::vector<Plant*> getAdjacentBeings(int logX, int logY, const int reach) const;


    /*!
     * \brief addBeing - add being to the board
     */
    void addBeing(Being*);

    /*!
     * \brief removeBeing - removes an animal from the board
     */
    void removeBeing(Animal*);

    /*!
     * \brief isFreeCell - checks, whether cell is free from animals
     * \param x, y - location we are curious in
     * \return result
     */
    bool isFreeCell(int x, int y);

    /*!
     * \brief checkCoordinate - checks, whether specified coordinate is allowed
     */
    std::function<bool(int, int)> checkCoordinate;


    /*!
     * \brief updateBeing - changes being board place
     * \param b - being, an animal
     * \param oldX, oldY - old coordinates of the animal
     *
     * depending on being current/old position, change logical being place
     */
    void updateBeing(Being* b, const int oldX, const int oldY);

    /*!
     * \brief beingsInterpolation get free place in between beings
     * \param a, b - two beings in between point we are looking for
     * \param coeff how close to the second being a point must be
     * \return interpolated free cell location
     */
    Point beingsInterpolation(const Being* a , const Being* b, const float& coeff = 0.5f);

    // Visitor interface
public:
    void visit(Plant *) override;
    void visit(Predator *) override;
    void visit(Herbivorous *) override;
};

#include "src/shared/board.tpp"

#endif // BOARD_H
