#ifndef MEANREPRODUCTION_H
#define MEANREPRODUCTION_H
#include "src/shared/parametersset.h"
#include "src/evolalg/eareproductiontype.h"

/*!
 * \brief The MeanReproduction class implementing mean reproduction method for the
 * Herbivorous and Predator populations from EA.
 */
class MeanReproduction: public EaReproductionType {
public:

    /*!
     * \brief reproducePopulation - providing functionality of Mean reproduction method for the temporary population using crossing-over.
     * \param tempPop - temporary population from evolutionary algorithm.
     */
    void reproducePopulation(QVector<std::shared_ptr<Animal> > &tempPop);
    /*!
     * MeanReproduction Destructor.
     */
    ~MeanReproduction() {}
};


#endif // MEANREPRODUCTION_H
