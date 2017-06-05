#ifndef MEANREPRODUCTION_H
#define MEANREPRODUCTION_H
#include "src/shared/parametersset.h"
#include "src/evolalg/eareproductiontype.h"


class MeanReproduction: public EaReproductionType {
public:
//    MeanReproduction() {}

    void reproducePopulation(QVector<Animal*>& tempPop);
    ~MeanReproduction() {}
};


#endif // MEANREPRODUCTION_H
