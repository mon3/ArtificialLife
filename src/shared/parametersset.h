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

enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};
enum Beings { PLANT, HERBIVOROUS, PREDATOR };

class Being;
class Animal;
class Herbivorous;
class Plant;
class BeingWindow;
typedef std::pair<int, int> Point;
class ParametersSet : public QObject
{
    Q_OBJECT
public:


    static ParametersSet* getInstance(int gridSize = 0);
    int getGridSize() const;
    Season getSeason();
    void setSeason(Season);
    static const int SCENE_WIDTH = 1000;
    static int BEING_WIDTH;
    ~ParametersSet() {  }
    Point beingsInterpolation(const Being*, const Being*, const float& coeff = 0.5f);


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
    static constexpr double foodCapacityCoeff = 50.0 ;
    static constexpr double exhLevelCoeff = -10.0; // the less value of exhLevel, the better


    void addBeing(Being*);

    //consider making position/location making class

    bool isFreeCell(int x, int y);
    void updateBeing(Being* b, const int oldX, const int oldY);

    // use polymorfism
    void removeBeing(Plant*);
    void removeBeing(Animal*);

    //getters
    int getMaxPlantHp() const;
    int getPlantGrowbackLevel() const;
    float getMaxFoodCapacity() const;
    static int getRandomInt(const int&, const int&);
    int getStartHungerLevel() const;


    // getters, more advanced for sugarscape
    template<typename T>
    std::vector<T> getAdjacentBeings(int logX, int logY, const int) const;

    std::vector<Plant*> getAdjacentBeings(int logX, int logY, const int) const;

    float getFoodConsumptionUnits() const;
    std::function<bool(int, int)> checkCoordinate;
public slots:
    void callWindow(Being* b);
private:

    int magic_offset;

    void mapPosition(Being* b);

    //to make singleton
    ParametersSet(const ParametersSet&) = delete;
    ParametersSet& operator=(const ParametersSet&) = delete;
    ParametersSet(int gridSize);



    static ParametersSet* instance;
    QSharedPointer<BeingWindow> window;

    // TODO: use smart pointers
    std::vector<std::vector <Plant* > > plantsOnBoard;
    std::vector<std::vector <Animal* > > animalsOnBoard;
    //game board params
    const int _gridSize;
    Season season;
    DayTime dayTime;



    //single creature params
    float biologicalChildAge;
    float biologicalAdultAge;
    int startHungerLevel = 70;
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


    //helper lambda functions

    std::function <int(int) > getRowMod;
    std::function< int(int) > getColMod;
};

#include "src/shared/parametersset.tpp"

#endif // PARAMETERSSET_H

