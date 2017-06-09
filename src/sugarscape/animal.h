#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
#include <functional>
#include "being.h"
#include "src/shared/board.h"
#include "src/evolalg/eapopulationinitializer.h"
#include <memory>


/*!
 * \ingroup sugarscape
 * \brief The Animal class - base class for animals - active participants of game
 *
 * Abstract; stores common features & logic & behaviour elements of animals
 */
class Animal : public Being
{
    Q_OBJECT
public:

    /*!
     * \brief Animal
     * \param logX_, logY - location of an animal
     */
    Animal(int logX_, int logY_) : Being(logX_, logY_) { activity = IDLE; }
    ~Animal(){}
    void action();
    virtual int type() const = 0;
    virtual std::unique_ptr<Animal> createBeing(int X, int Y, QVector<int> features, QVector<double> stdDevs) = 0;
    virtual void setFeaturesForEA(QVector<int>& vals) = 0;
    virtual QVector<int> featuresToChromosome() = 0;
    virtual void acceptInitializer(EaPopulationInitializer& eaInit, int X, int Y) = 0;

    double randomDouble(double min, double max);

    // for feature and stdDevs used in EA
    struct FeatureStd{
       FeatureStd(int value, double stdDev):feature(value), stdDev(stdDev){} // do inicjalizacji w taki sposob
       int feature;
       double stdDev;
    };

    virtual void setFeatureStdevs(FeatureStd Eye, FeatureStd Speed, FeatureStd HitPoints, FeatureStd Metabolism, FeatureStd FoodCapacity, FeatureStd ExhLevel) = 0;

    /// Set of possible animal states
    enum Activity {
        HUNTING, ///<  State, in which animal is hungry and looking for food
        IDLE, ///<  State, in which animal is saturated and doing nothing
        RUNNNING_AWAY, ///< State, in which animal is scared and looking for safe place
        DEAD ///< Animal is dead and must be removed from the board
    };
    Q_ENUM(Activity)

    void setEyeSight(int value);
    int getEyeSight() const;

    void setAge(int value);
    int getAge() const;

    void setGeneration(int value);
    int getGeneration() const;

    void setSpeed(int value);
    int getSpeed() const;

    void setMetabolism(int value);
    int getMetabolism() const;

    void setFoodCapacity(int value);
    int getFoodCapacity() const;

    void setExhaustionLevel(int value);
    int getExhaustionLevel() const;

    void setSaturationRate(int value);
    int getSaturationRate() const;

    void setStdDevs(QVector<double> vals);
    QVector<double> getStdDevs() const;

public:
    QVector<int> getFeaturesEA() const;

    void displayStd() const;
    void displayFeatures() const;
    double normalizeFeature(int feature,int min, int max);

    Activity getActivity() const;
    QVector<int> featuresToVectorEA(int eye, int speed, int hitPoints, int metabolism, int foodCapacity, int exhLevel);
    void setFeaturesEA(QVector<int> vals);
    virtual void accept(Visitor *) override = 0; ///< implementation of a visitor pattern
protected:
    /*!
     * \brief foodConsumptionRule how food must be consumed
     * \param foodValue value of food in food units
     */
    void foodConsumptionRule(int& foodValue);

protected:

    //subactions
    //set of subactions for every type of animal will be defined:


    // TODO: consider to make a template function
    /*!
     * \brief Hunt hunting activity
     * \details Different for predators & herbivorous
     *
     * \return selected prey
     */
    virtual Being* hunt() = 0;
    /*!
     * \brief eat - eating, different due to different type of prey
     *  \param b - prey
     */
    virtual void eat(Being* b) = 0;
    /*!
     * \brief findEnemies Finds potentional treacherous enemie
     * \return vector of possible enemies
     */
    virtual std::vector<Animal*> findEnemies() = 0;

private:
    /*!
     * \brief move - moving to location, specified by x / y
     * \param x, y - logical coordinates , if not given, assume random location
     */
    void move(int x = UNKNOWN_LOCATION, int y = UNKNOWN_LOCATION);
    /*!
     * \brief moveClose - get as close as you can to desired location
     * \param goalX, goalY - logical coordinates
     */
    void moveClose(int goalX,int goalY);
    /*!
     * \brief runFrom - run to safe place from enemies
     * \param enemies - the most dangerous enemies
     */
    void runFrom(const std::vector<Animal*>& enemies);

    //routine functions, to simplify action()
    /*!
     * \brief huntRoutine - hunting routine similar to all animals
     */
    void huntRoutine();
    /*!
     * \brief enemiesHandlingRoutine - how to deal with enemies
     *
     * \details similar for all animals
     */
    void enemiesHandlingRoutine();
    /*!
     * \brief foodConsumptionRoutine - consume food
     *
     * \details Consumes food, stores rest as inner reserve
     */
    void foodConsumptionRoutine();
    /*!
     * \brief exaustionLevelHandlingRoutine - increment \ decrement exaustion
     *
     * Depending on animal activity, different exaustion level assumed
     */
    void exaustionLevelHandlingRoutine();


    /*!
     * \brief eyeSight -  how far animal can see
     *
     * \details feature used in EA
     */
    int eyeSight;
    int age; ///< how old is the animal
    int generation; ///< animal generation
    int speed; ///< how far animal can get in one turn; feature used in EA
    int foodCapacity; ///< how much animal can store; feature used in EA
    int metabolism; ///< how much food units animal consumes in one turn; feature used in EA
    int exhaustionLevel; ///< how exausted is an animal feature used in EA
    int saturationRate; ///< level of saturation of an animal; feature used in EA

    Activity activity; ///< current animal activity

    QVector<int> featuresEA; ///< standard deviations for evolutionary algorithm
    QVector<double> stdDevs; ///< standard deviations for evolutionary algorithm

    static const int UNKNOWN_LOCATION = -1; ///<  undefined grid location

    const static std::function<int(int)> direction; ///< in which direction animal should move

};

#endif // ANIMAL_H
