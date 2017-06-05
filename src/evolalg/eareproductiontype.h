#ifndef EAREPRODUCTIONTYPE_H
#define EAREPRODUCTIONTYPE_H
#include<QVector>
#include "src/sugarscape/animal.h"
#include "src/sugarscape/predator.h"
#include "src/sugarscape/herbivorous.h"

class EaReproductionType {
protected:
    EaReproductionType() {}

public:
    virtual void reproducePopulation(QVector<Animal*>& tempPop) = 0;// type: mean, interpolation
    virtual ~EaReproductionType() {}

};



#endif // EAREPRODUCTIONTYPE_H
