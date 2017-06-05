#ifndef EAPOPULATIONINITIALIZER_H
#define EAPOPULATIONINITIALIZER_H

class Herbivorous;
class Predator;

// visitor class for EA population initialization
class EaPopulationInitializer
{
public:
    virtual void initialize(Herbivorous& herb, int X, int Y) = 0;
    virtual void initialize(Predator& pred, int X, int Y) = 0;
};


#endif // EAPOPULATIONINITIALIZER_H
