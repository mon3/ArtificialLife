#ifndef HERBIVOROUS_H
#define HERBIVOROUS_H
#include "animal.h"

class Herbivorous : public Animal
{
public:
    Herbivorous(int logX, int logY) : Animal(logX, logY) { }

    // Being interface
private:
    virtual int getPenColor() const { return Qt::green; }
};

#endif // HERBIVOROUS_H
