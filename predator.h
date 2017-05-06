#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"

class Predator : public Animal
{
    Q_OBJECT
public:
    Predator(int x, int y) : Animal(x, y) { }
    int type() const { return Beings::PREDATOR; }
    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::red; }
};

#endif // PREDATOR_H
