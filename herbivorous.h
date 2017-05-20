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
    Herbivorous(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity,
             int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs);

    Herbivorous(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism,  int foodCapacity,
              int exhaustionLevel, QVector<double> stdDevs);

    Herbivorous(int x, int y, QVector<int> features, QVector<double> stdDevs);


    int type() const { return Beings::HERBIVOROUS; }
    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::green; }



    // Animal interface
private:

//    Being* hunt() override;
//    void eat(Being*) override;
};

#endif // HERBIVOROUS_H
