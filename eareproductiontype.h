#ifndef EAREPRODUCTIONTYPE_H
#define EAREPRODUCTIONTYPE_H
#include<QVector>
#include<animal.h>
#include <predator.h>
#include <herbivorous.h>

class EaReproductionType {
protected:
    EaReproductionType();

public:
    virtual void reproducePopulation(QVector<Animal*>& tempPop) = 0;// type: mean, interpolation

};



#endif // EAREPRODUCTIONTYPE_H
