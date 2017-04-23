#ifndef PARAMETERSSET_H
#define PARAMETERSSET_H

enum Season {winter, spring, summer, autumn};
enum DayTime {day, night};


class ParametersSet
{
public:
<<<<<<< HEAD
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
=======
    ParametersSet();
private:
    float biologicalChildAge;
    float biologicalAdultAge;
    int gridSize;
    Season season;
    DayTime dayTime;
>>>>>>> multi_dev
    float crossoverProbability;
    float mutationProbability;
    float mutationFactor;

<<<<<<< HEAD

    //plants appearance params
=======
>>>>>>> multi_dev
    float plantAppearance;
    int minPlantSum;
    int maxPlantSum;
    float plantToSizeFactor;
<<<<<<< HEAD
=======
    //evolution alg params

    //plants appearance params

>>>>>>> multi_dev
};

#endif // PARAMETERSSET_H
