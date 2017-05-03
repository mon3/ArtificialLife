#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"

class Predator : public Animal
{
public:
    Predator(int x, int y) : Animal(x, y) { }
};

#endif // PREDATOR_H
