#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"
#include "herbivorous.h"

class Predator : public Animal
{
    Q_OBJECT
public:

    void setFeaturesForEA(QVector<int>& vals);
    QVector<int> featuresToChromosome();
    void setFeatureStdevs(FeatureStd Eye, FeatureStd Speed, FeatureStd HitPoints , FeatureStd Metabolism, FeatureStd FoodCapacity, FeatureStd ExhLevel);
    virtual void acceptInitializer(EaPopulationInitializer& eaInit, int X, int Y) {eaInit.initialize(*this, X, Y);}

    Predator(int x, int y);
    Predator(int x, int y, QVector<int> features, QVector<double> stdDevs);
    Predator(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity,
             int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs);
    Predator(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism,  int foodCapacity,
              int exhaustionLevel, QVector<double> stdDevs);

    int type() const { return Beings::PREDATOR; }


    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::red; }

    // Animal interface
private:
    Being* hunt();


private:
    // Animal interface
    void eat(Being *) override;

    // Animal interface
protected:
    vector<Animal*> findEnemies() override;

};

#endif // PREDATOR_H
