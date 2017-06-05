#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"
#include "herbivorous.h"
/*!
 * \brief The Predator class
 * Hunts herbivorous; has no natural enemies
 */
class Predator : public Animal
{
    Q_OBJECT
public:

    void setFeaturesForEA(QVector<int>& vals);
    QVector<int> featuresToChromosome();
    void setFeatureStdevs(FeatureStd Eye, FeatureStd Speed, FeatureStd HitPoints , FeatureStd Metabolism, FeatureStd FoodCapacity, FeatureStd ExhLevel);
    virtual void acceptInitializer(EaPopulationInitializer& eaInit, int X, int Y) {eaInit.initialize(*this, X, Y);}
    virtual std::unique_ptr<Animal> createBeing(int X, int Y, QVector<int> features, QVector<double> stdDevs)
    {    return std::unique_ptr<Animal>((new Predator(X, Y, features, stdDevs))); }


    Predator(int x, int y);
    Predator(int x, int y, QVector<int> features, QVector<double> stdDevs);
    Predator(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity,
             int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs);
    Predator(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism,  int foodCapacity,
              int exhaustionLevel, QVector<double> stdDevs);

    int type() const { return Beings::PREDATOR; }


    // Animal interface
private:
    Being* hunt();
    // Animal interface
    void eat(Being *) override;

    // Animal interface
protected:
    std::vector<Animal*> findEnemies() override;


    // Being interface
public:
    void accept(Visitor *) override;
};

#endif // PREDATOR_H
