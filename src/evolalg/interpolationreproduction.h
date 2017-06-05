#ifndef INTERPOLATIONREPRODUCTION_H
#define INTERPOLATIONREPRODUCTION_H
#include "src/evolalg/eareproductiontype.h"


/*!
 * \brief The InterpolationReproduction class implementing Interpolation reproduction method for the
 * Herbivorous and Predator populations from EA.
 */

class InterpolationReproduction: public EaReproductionType {
public:
    /*!
     * \brief reproducePopulation - providing functionality of Interpolation to reproduce the temporary population using crossing-over.
     * \param tempPop - temporary population from evolutionary algorithm.
     */
    void reproducePopulation(QVector<std::shared_ptr<Animal>>& tempPop);
    /*!
     *  InterpolationReproduction Destructor.
     */
    ~InterpolationReproduction(){}
};



#endif // INTERPOLATIONREPRODUCTION_H
