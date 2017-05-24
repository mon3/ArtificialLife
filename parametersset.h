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

using namespace std;
enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};
enum Beings { PLANT, HERBIVOROUS, PREDATOR };

class Being;
class Animal;
class Herbivorous;
class Plant;
class BeingWindow;
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
    static int getRandomInt();
    float getStartHungerLevel() const;


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
    static constexpr double hitPointsCoeff = 10.0 ;
    static constexpr double metabolismCoeff = 2.0 ;
    static constexpr double foodCapacityCoeff = 10.0 ;
    static constexpr double exhLevelCoeff = -1.0; // the less value of exhLevel, the better

    //TODO : use a template?
    vector<Plant *> getAdjacentPlants(Animal*) const;
    vector<Herbivorous*> getAdjacentHerbivorous(Animal*) const;


    int getPlantGrowbackLevel() const;

public slots:
    void callWindow(Being* b);
private:
    //to make singleton
    ParametersSet(const ParametersSet&) = delete;
    ParametersSet& operator=(const ParametersSet&) = delete;
    ParametersSet(int gridSize);



    static ParametersSet* instance;
    QSharedPointer<BeingWindow> window;


    vector<vector <Plant* > > plantsOnBoard;
    vector<vector <Animal* > > animalsOnBoard;
    //game board params
    const int _gridSize;
    Season season;
    DayTime dayTime;



    //single creature params
    float biologicalChildAge;
    float biologicalAdultAge;
    float startHungerLevel;

    //genetic algorithm params
    float crossoverProbability;
    float mutationProbability;
    float mutationFactor;


    //plants appearance params
    float plantAppearance;
    int minPlantSum;
    int maxPlantSum;
    float plantToSizeFactor;
    int plantGrowbackLevel;
    const int MAX_PLANT_HP_LEVEL = 100;


    //helper lambda functions
    function<bool(int, int)> checkCoordinate;
    function<int(int)> getRowMod;
    function<int(int)> getColMod;
};


#endif // PARAMETERSSET_H

