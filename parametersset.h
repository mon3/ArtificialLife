#ifndef PARAMETERSSET_H
#define PARAMETERSSET_H

#include <QObject>
#include <QSharedPointer>
#include <stdlib.h>
enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};
enum Beings { PLANT, HERBIVOROUS, PREDATOR };

class Being;
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
public slots:
    void callWindow(Being* b);
private:
    //to make singleton
    ParametersSet(const ParametersSet&) = delete;
    ParametersSet& operator=(const ParametersSet&) = delete;
    ParametersSet(int gridSize);


    static ParametersSet* instance;
    QSharedPointer<BeingWindow> window;

    //Beings board[][];
    //game board params
    const int _gridSize;
    Season season;
    DayTime dayTime;

    //single creature params
    float biologicalChildAge;
    float biologicalAdultAge;


    //genetic algorithm params
    float crossoverProbability;
    float mutationProbability;
    float mutationFactor;


    //plants appearance params
    float plantAppearance;
    int minPlantSum;
    int maxPlantSum;
    float plantToSizeFactor;
};


#endif // PARAMETERSSET_H

