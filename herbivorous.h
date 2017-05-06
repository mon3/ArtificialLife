#ifndef HERBIVOROUS_H
#define HERBIVOROUS_H
#include "animal.h"

class Herbivorous : public Animal
{
public:
    Herbivorous(int logX, int logY) : Animal(logX, logY) { }

    int type() const { return Beings::HERBIVOROUS; }
    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::red; }
};

#endif // HERBIVOROUS_H
