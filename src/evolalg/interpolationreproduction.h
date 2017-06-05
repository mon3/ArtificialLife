#ifndef INTERPOLATIONREPRODUCTION_H
#define INTERPOLATIONREPRODUCTION_H
#include "src/evolalg/eareproductiontype.h"



class InterpolationReproduction: public EaReproductionType {
public:
//    InterpolationReproduction() {}

    void reproducePopulation(QVector<Animal*>& tempPop);
    ~InterpolationReproduction(){}
};



#endif // INTERPOLATIONREPRODUCTION_H
