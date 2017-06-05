#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "src/evolalg/eareproductiontype.h"
#include "src/sugarscape/animal.h"
#include "src/evolalg/meanreproduction.h"
#include "src/evolalg/interpolationreproduction.h"

/*!
 * \brief The Reproduction class - allowing reproduction of the population from EA depending on the type.
 * Based on Startegy Pattern.
 */
class Reproduction
{
public:
    /*!
    * \brief The StrategyType enum - reproduction strategy type: Mean(0), Interpolation(1).
    * Mean: 0.25*features of 1st parent, 0.75*features of 2nd parent.
    * Interpolation: a(random)*features of 1st parent, (1-a)*features of 2nd parent.
    */
   enum StrategyType
   {
       Mean,Interpolation
   };
   /*!
    * \brief Reproduction Constructor.
    */
   Reproduction();

   /*!
    * \brief setStrategy - method allowing to set certain type of reproduction: mean, interpolation.
    * \param type - reproduction type that should be used in EA.
    */
   void setStrategy(int type);
   /*!
    * \brief reproduce - method providing reproduction functionality in EA.
    * The proper method of reproduction is called depending on the type set before.
    * \param tempPop - temporary population which will be reproduced.
    */
   void reproduce(QVector<std::shared_ptr<Animal>> &tempPop);


 private:
   /*!
    * \brief strategy_ - holder for different reproduction strategies.
    */
   EaReproductionType *strategy_;
};




#endif // REPRODUCTION_H
