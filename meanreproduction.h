#ifndef MEANREPRODUCTION_H
#define MEANREPRODUCTION_H
#include<eareproductiontype.h>


class MeanReproduction: public EaReproductionType {
public:
    MeanReproduction() {}

    void reproducePopulation(QVector<Animal*>& tempPop);
};


#endif // MEANREPRODUCTION_H
