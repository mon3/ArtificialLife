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


    //TODO : use some template?
    vector<Being *> getAdjacentHuntSubjects(Animal*) const;

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

    //helper lambda functions
    function<bool(int, int)> checkCoordinate;
    function<int(int)> getRowMod;
    function<int(int)> getColMod;
};


#endif // PARAMETERSSET_H

