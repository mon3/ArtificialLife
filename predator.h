#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"
#include "herbivorous.h"
#include <constrainedvalue.cpp>


typedef ConstrainedValue<int, ParametersSet::minEyeSight, ParametersSet::maxEyeSight> ConstrainedEyeSight;
typedef ConstrainedValue<int, ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed> ConstrainedPredatorSpeed;
typedef ConstrainedValue<int, ParametersSet::minHitPoints, ParametersSet::maxHitPoints> ConstrainedHitPoints;
typedef ConstrainedValue<int, ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism> ConstrainedPredatorMetabolism;
typedef ConstrainedValue<int, ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity> ConstrainedPredatorFoodCapcity;
typedef ConstrainedValue<int, ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel> ConstrainedExhLevel;


class Predator : public Animal
{
    Q_OBJECT
public:


    Predator(int x, int y) : Animal(x, y) { }
    Predator(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity,
             int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs);
    Predator(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism,  int foodCapacity,
              int exhaustionLevel, QVector<double> stdDevs);
    Predator(int x, int y, ConstrainedEyeSight es, ConstrainedPredatorSpeed speed, ConstrainedHitPoints hp,
                       ConstrainedPredatorMetabolism metab, ConstrainedPredatorFoodCapcity fc, ConstrainedExhLevel exhLev,
                       QVector<double> stdDevs);


    Predator(int x, int y, QVector<int> features, QVector<double> stdDevs);

//    Predator(QVector<int> features, QVector<double> stdDevs);

    int type() const { return Beings::PREDATOR; }
    void setPredEyeSightConstr(ConstrainedEyeSight eyeSightConstr);
    void setPredHitPointsConstr(ConstrainedHitPoints hitPointsConstr);
    void setPredFoodCapacityConstr(ConstrainedPredatorFoodCapcity foodCapacityConstr);
    void setPredMetabolismConstr(ConstrainedPredatorMetabolism metabolismConstr);
    void setPredExhLevel(ConstrainedExhLevel exhLevelConstr);
    void setPredSpeedConstr(ConstrainedPredatorSpeed speedConstr);


    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::red; }

    // Animal interface
private:
    Being* hunt();


private:
    // Animal interface
    void eat(Being *) override;

private:
    ConstrainedEyeSight eyeSightConstr_;
    ConstrainedHitPoints hitPointsConstr_;
    ConstrainedPredatorFoodCapcity foodCapacityConstr_;
    ConstrainedPredatorMetabolism metabolismConstr_;
    ConstrainedExhLevel exhLevelConstr_;
    ConstrainedPredatorSpeed speedConstr_;


    // Animal interface
protected:
    vector<Animal*> findEnemies() override;

};

#endif // PREDATOR_H
