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
    vector<T> getAdjacentBeings(const Animal* a, const int) const;

    vector<Plant*> getAdjacentBeings(const Animal* a, const int) const;

    float getFoodConsumptionUnits() const;
    function<bool(int, int)> checkCoordinate;
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
    vector<vector <Plant* > > plantsOnBoard;
    vector<vector <Animal* > > animalsOnBoard;
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
    int plantGrowbackLevel;
    const int MAX_PLANT_HP_LEVEL = 100;


    //helper lambda functions

    function<int(int)> getRowMod;
    function<int(int)> getColMod;
};

#include "parametersset.tpp"

#endif // PARAMETERSSET_H

