#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include<eareproductiontype.h>
#include<animal.h>
#include<meanreproduction.h>
#include<interpolationreproduction.h>


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
