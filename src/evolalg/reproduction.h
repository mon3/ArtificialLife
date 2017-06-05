#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include "src/evolalg/eareproductiontype.h"
#include "src/sugarscape/animal.h"
#include "src/evolalg/meanreproduction.h"
#include "src/evolalg/interpolationreproduction.h"


class Reproduction
{
public:
   enum StrategyType
   {
       Mean,Interpolation
   };
   Reproduction();

   void setStrategy(int type);
   void reproduce(QVector<Animal *> &tempPop);


 private:
   EaReproductionType *strategy_;
};




#endif // REPRODUCTION_H
