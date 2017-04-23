#ifndef PARAMETERSSET_H
#define PARAMETERSSET_H

enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};


class ParametersSet
{
public:
    ParametersSet(int _gridSize) : gridSize(_gridSize) { }
    int getGridSize() const;

private:
    //game board params
    const int gridSize;
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
