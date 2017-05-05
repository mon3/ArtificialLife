#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"

class Predator : public Animal
{
public:
    Predator(int x, int y) : Animal(x, y) { }

    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::red; }
};

#endif // PREDATOR_H
