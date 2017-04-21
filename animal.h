#ifndef ANIMAL_H
#define ANIMAL_H

#include "creature.h"

enum Activity {
    MATING,
    HUNTING, //for herbios ?
    RESTING,
    SLEEPING,
    NURSING,
    RUNNNING_AWAY,
    DEAD
};

class Animal : public Being
{
public:
    Animal();
    void action();
private:
    //subactions
    //set of subactions for every type of animal will be defined:
    virtual void hunt(Being&);



    void mate(Animal& );
    void eat(Being&);
    void rest();
    void sleep();
    // list of Beings checkingNeighbourhood();
    void run();


    int eveSight;
    int age;
    const int generation;
    int speed;
    float exaustionLevel;
    float saturationRate;
    Activity activity;
};

#endif // ANIMAL_H
