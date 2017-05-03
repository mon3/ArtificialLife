#ifndef PARAMETERSSET_H
#define PARAMETERSSET_H

#include <QObject>

enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};
enum Beings { PLANT, HERBIVOROUS, PREDATOR };

class ParametersSet
{
public:
    ParametersSet(int gridSize) : _gridSize(gridSize) {}
    int getGridSize() const;
    Season getSeason();
    void setSeason(Season);
    static const int SCENE_WIDTH = 1000;
    ~ParametersSet() { }

private:
    Beings board[][];
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

Q_DECLARE_METATYPE(Season)

#endif // PARAMETERSSET_H

