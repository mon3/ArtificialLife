#ifndef PARAMETERSSET_H
#define PARAMETERSSET_H

enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};


class ParametersSet
{
public:
    ParametersSet();
private:
    float biologicalChildAge;
    float biologicalAdultAge;
    int gridSize;
    Season season;
    DayTime dayTime;
    float crossoverProbability;
    float mutationProbability;
    float mutationFactor;

    float plantAppearance;
    int minPlantSum;
    int maxPlantSum;
    float plantToSizeFactor;
    //evolution alg params

    //plants appearance params

};

#endif // PARAMETERSSET_H
