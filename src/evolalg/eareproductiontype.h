#ifndef EAREPRODUCTIONTYPE_H
#define EAREPRODUCTIONTYPE_H
#include<QVector>
#include "src/sugarscape/animal.h"
#include "src/sugarscape/predator.h"
#include "src/sugarscape/herbivorous.h"

/*!
 * \brief The EaReproductionType class
 * Allows to reproduce the population depending on reproduction type:
 * mean(0), interpolation(1). Using Strategy Pattern.
 */
class EaReproductionType {
protected:
    /*!
     * \brief EaReproductionType Constructor.
     */
    EaReproductionType() {}

public:
    /*!
     * \brief reproducePopulation of Animals depending on the type of reproduction.
     * Reproduction type: mean(0), interpolation(1).
     * \param tempPop - temporary population from Evolutionary Algorithm that
     * will be reproduced.
     */
    virtual void reproducePopulation(QVector<std::shared_ptr<Animal>>& tempPop) = 0;
    /*!
     * \brief ~EaReproductionType Destructor.
     */
    virtual ~EaReproductionType() {}

};



#endif // EAREPRODUCTIONTYPE_H
