#ifndef EAPOPULATIONINITIALIZER_H
#define EAPOPULATIONINITIALIZER_H

class Herbivorous;
class Predator;


/**
*   Class for Evolutionary Algorithm Population initialization. Using Visitor Design Pattern.
*
 */
// visitor class for EA population initialization
class EaPopulationInitializer
{
public:
    /*!
     * \brief initialize - virtual function for initialization of a new individual
     * for Herivorous Population.
     * \param herb - individual from Herbivorous Population.
     * \param X - logical position X of indvidual on the board.
     * \param Y - logical position Y of individual on the board.
     */

    virtual void initialize(Herbivorous& herb, int X, int Y) = 0;
    /*!
     * \brief initialize - virtual function for initialization of a new individual
     * for Predator Population.
     * \param herb - individual from Predator Population.
     * \param X - logical position X of indvidual on the board.
     * \param Y - logical position Y of individual on the board.
     */
    virtual void initialize(Predator& pred, int X, int Y) = 0;
};


#endif // EAPOPULATIONINITIALIZER_H
