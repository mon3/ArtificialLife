#ifndef HERBIVOROUS_H
#define HERBIVOROUS_H
#include <limits>
#include <iterator>
#include "animal.h"
#include "plant.h"
class Herbivorous : public Animal
{
    Q_OBJECT
public:
    Herbivorous(int logX, int logY) : Animal(logX, logY) { }

    int type() const { return Beings::HERBIVOROUS; }
    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::green; }



    // Animal interface
private:

    Being* hunt() override;
    void eat(Being*) override;
};

#endif // HERBIVOROUS_H
