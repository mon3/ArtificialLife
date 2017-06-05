#ifndef EAINITIALIZER_H
#define EAINITIALIZER_H
#include "src/evolalg/eapopulationinitializer.h"
#include "src/sugarscape/herbivorous.h"
#include "src/sugarscape/predator.h"
#include "src/evolalg/generator.h"

class EaInitializer: public EaPopulationInitializer
{
public:
    void initialize(Herbivorous& herb, int X, int Y);
    void initialize(Predator& pred, int X, int Y);
};


#endif // EAINITIALIZER_H
