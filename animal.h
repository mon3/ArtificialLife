#ifndef ANIMAL_H
#define ANIMAL_H

#include "creature.h"

enum Activity {
    MATING,
<<<<<<< HEAD
    HUNTING, //for herbios ?
=======
    HUNTING, //for herbivorous ?
>>>>>>> multi_dev
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
<<<<<<< HEAD
    virtual void hunt(Being&);
=======
    virtual void hunt(Being& )=0;
>>>>>>> multi_dev



    void mate(Animal& );
    void eat(Being&);
    void rest();
    void sleep();
    // list of Beings checkingNeighbourhood();
    void run();


    int eveSight;
    int age;
<<<<<<< HEAD
    const int generation;
=======
//    const int generation;
    int generation;
>>>>>>> multi_dev
    int speed;
    float exaustionLevel;
    float saturationRate;
    Activity activity;
};

#endif // ANIMAL_H
