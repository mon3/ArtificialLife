#ifndef EAINITIALIZER_H
#define EAINITIALIZER_H
#include <eapopulationinitializer.h>
#include <herbivorous.h>
#include <predator.h>
#include <generator.h>

class EaInitializer: public EaPopulationInitializer
{
public:
    void initialize(Herbivorous& herb, int X, int Y);
    void initialize(Predator& pred, int X, int Y);
};


#endif // EAINITIALIZER_H
