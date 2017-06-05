#ifndef HERBIVOROUS_H
#define HERBIVOROUS_H
#include <limits>
#include <iterator>
#include  "src/sugarscape/animal.h"
#include "src/sugarscape/plant.h"

class Herbivorous : public Animal
{
    Q_OBJECT
public:
    void setFeaturesForEA(QVector<int>& vals);
    QVector<int> featuresToChromosome();
    void setFeatureStdevs(FeatureStd Eye, FeatureStd Speed, FeatureStd HitPoints , FeatureStd Metabolism, FeatureStd FoodCapacity, FeatureStd ExhLevel);
    virtual void acceptInitializer(EaPopulationInitializer& eaInit, int X, int Y) {eaInit.initialize(*this, X, Y);}


    Herbivorous(int logX, int logY);
    Herbivorous(int x, int y, QVector<int> features, QVector<double> stdDevs);
    Herbivorous(int x, int y, int hitPoints, int eyeSight, int age, int generation, int speed, int foodCapacity,
             int metabolism, int exhaustionLevel, int saturationRate, QVector<double> stdDevs);
    Herbivorous(int x, int y, int eyeSight, int speed, int hitPoints, int metabolism,  int foodCapacity,
              int exhaustionLevel, QVector<double> stdDevs);



    int type() const { return Beings::HERBIVOROUS; }
    void accept(Visitor *) override;
    // Being interface
private:
    inline virtual Qt::GlobalColor getPenColor() const { return Qt::green; }



    // Animal interface
private:

 
    Being* hunt() override;
    void eat(Being*) override;

    // Animal interface
protected:
    std::vector<Animal*> findEnemies() override; 
};

#endif // HERBIVOROUS_H
