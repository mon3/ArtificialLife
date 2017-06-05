#ifndef EAINITIALIZER_H
#define EAINITIALIZER_H
#include "src/evolalg/eapopulationinitializer.h"
#include "src/sugarscape/herbivorous.h"
#include "src/sugarscape/predator.h"
#include "src/evolalg/generator.h"



/*!
 * \brief The EaInitializer class
 *
 * Class initializing EaInitializer providing prover
 * individual initialization depending on its' type:
 * Hebivorous or Predator.
 *
 */
class EaInitializer: public EaPopulationInitializer
{
public:
    /*!
     * \brief initialize Herbivorous individual
     *
     * Function providing initialization of the individual of Herbivorous Population.
     * \param herb - individual, for which proper features and stdDevs for Evolutionary
     * Algorithm will be initialized.
     * \param X - logical position X of indvidual on the board.
     * \param Y - logical position Y of individual on the board.
     */
    void initialize(Herbivorous& herb, int X, int Y);

    /*!
     * \brief initialize Predator individual
     *
     * Function providing initialization of the individual of Predator Population.
     * \param herb - individual, for which proper features and stdDevs for Evolutionary
     * Algorithm will be initialized.
     * \param X - logical position X of indvidual on the board.
     * \param Y - logical position Y of individual on the board.
     */
    void initialize(Predator& pred, int X, int Y);
};


#endif // EAINITIALIZER_H
