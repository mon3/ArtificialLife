#ifndef PARAMETERSSET_H
#define PARAMETERSSET_H

#include <QObject>
#include <QSharedPointer>
#include <memory>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>

/*! \defgroup shared Defines shared objects we can call from every place in application */

/*!
 * \brief The Beings enum, corresponds with it's type
 */
enum Beings {
    PLANT,
    HERBIVOROUS,
    PREDATOR
};

class Being;
class Animal;
class Herbivorous;
class Plant;
class BeingWindow;
typedef std::pair<int, int> Point;
/*!
 * \brief The ParametersSet class
 * Keep's common game parameters, singletone
 *
 * \ingroup shared
 */
class ParametersSet : public QObject
{
    Q_OBJECT
public:


    static ParametersSet* getInstance(int gridSize = 0);
    int getGridSize() const;

    static const int SCENE_WIDTH = 1000;
    static int BEING_WIDTH;
    ~ParametersSet() {  }



    // COMMON for predator and herbivorous
    static const int minHitPoints = 0;
    static const int maxHitPoints = 100;

    static const int minExhaustionLevel = 0;
    static const int maxExhaustionLevel = 100;

    static const int minEyeSight = 1;
    static const int maxEyeSight = 6;

    static const int minAge = 0;
    static const int maxAge = 100;

    // DIFFERENT

    static const int minPredatorSpeed = 1;
    static const int maxPredatorSpeed = 5;

    static const int minHerbivorousSpeed = 1;
    static const int maxHerbivorousSpeed = 3;

    static const int minPredatorFoodCapacity= 1600;// 2*SaturaionRate
    static const int maxPredatorFoodCapacity = 8000;

    static const int minHerbivorousFoodCapacity= 1000;
    static const int maxHerbivorousFoodCapacity = 3000;

    static const int minHerbivorousMetabolism = 15;
    static const int maxHerbivorousMetabolism = 300;

    static const int minPredatorMetabolism = 50;
    static const int maxPredatorMetabolism = 600;

    static const int minHerbivorousSaturationRate = 500;
    static const int maxHerbivorousSaturationRate = 1500;

    static const int minPredatorSaturationRate = 800;
    static const int maxPredatorSaturationRate = 4000;

    // features coefficients for fitness function calculation
    static constexpr double eyeSightCoeff = 15.0 ;
    static constexpr double speedCoeff = 14.0 ;
    static constexpr double hitPointsCoeff = 22.5;
    static constexpr double metabolismCoeff = 8.0 ;
    static constexpr double foodCapacityCoeff = 25.0 ; // before:50
    static constexpr double exhLevelCoeff = -12.5; // the less value of exhLevel, the better; before: -10



    //getters
    int getMaxPlantHp() const;
    int getPlantGrowbackLevel() const;
    float getMaxFoodCapacity() const;
    static int getRandomInt(const int&, const int&);
    int getStartHungerLevel() const;

    float getFoodConsumptionUnits() const;
public slots:
    void callWindow(Being* b);
private:
    //to make singleton
    ParametersSet(const ParametersSet&) = delete;
    ParametersSet& operator=(const ParametersSet&) = delete;
    ParametersSet(int gridSize);
    static ParametersSet* instance;

    QSharedPointer<BeingWindow> window;

    const int _gridSize;



    //single creature params
    float biologicalChildAge;
    float biologicalAdultAge;
    int startHungerLevel = 80;
    float maxFoodCapacity;
    float foodConsumptionUnits;

    //genetic algorithm params
    float crossoverProbability;
    float mutationProbability;
    float mutationFactor;


    //plants appearance params
    float plantAppearance;
    int minPlantSum;
    int maxPlantSum;
    float plantToSizeFactor;
    int plantGrowbackLevel = 30;
    const int MAX_PLANT_HP_LEVEL = 100;
};


#endif // PARAMETERSSET_H

