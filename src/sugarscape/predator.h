#ifndef PREDATOR_H
#define PREDATOR_H
#include "animal.h"
#include "herbivorous.h"
/*!
 * \brief The Predator class
 * Hunts herbivorous; has no natural enemies, eats herbivorous
 *
 * \ingroup sugarscape
 */
class Predator : public Animal
{
    Q_OBJECT
public:

    void setFeaturesForEA(QVector<int>& vals);
    QVector<int> featuresToChromosome();
    void setFeatureStdevs(FeatureStd Eye, FeatureStd Speed, FeatureStd HitPoints , FeatureStd Metabolism, FeatureStd FoodCapacity, FeatureStd ExhLevel);
    virtual void acceptInitializer(EaPopulationInitializer& eaInit, int X, int Y) {eaInit.initialize(*this, X, Y);}
    virtual std::unique_ptr<Animal> createBeing(int X, int Y, QVector<int> features, QVector<double> stdDevs_)
    {    return std::unique_ptr<Animal>((new Predator(X, Y, features, stdDevs_))); }

    Predator(const Predator& other);
    Predator(int x, int y);
    Predator(int x, int y, QVector<int> features, QVector<double> stdDevs);
    /*!
     * \brief Predator Constructor of the Predator
     * \param x, y - location of an animal
     * \param hitPoints base health
     * \param eyeSight How far predator can see
     * \param age Age, how many turns did the animal lived
     * \param generation In which generation being was born
     * \param speed how far animal can get in one turn
     * \param foodCapacity how much food animal can carry
     * \param metabolism how many food units animal consumes in one turn
     * \param exhaustionLevel how exausted animal is
     * \param saturationRate how saturated animal is
     * \param stdDevs features from evolution algorithm
     */
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
