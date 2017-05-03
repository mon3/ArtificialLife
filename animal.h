#ifndef ANIMAL_H
#define ANIMAL_H

#include "being.h"

enum Activity {
    MATING,
    HUNTING, //for herbivorous ?
    RESTING,
    SLEEPING,
    NURSING,
    RUNNNING_AWAY,
    DEAD
};

class Animal : public Being
{
public:
    Animal(int _logX, int _logY) : Being(_logX, _logY) { }
    void action();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    //subactions
    //set of subactions for every type of animal will be defined:
//    virtual void hunt(Being& )=0;



    void mate(Animal& );
    void eat(Being&);
    void rest();
    void sleep();
    // list of Beings checkingNeighbourhood();
    void run();


    int eveSight;
    int age;
//    const int generation;
    int generation;
    int speed;
    float exaustionLevel;
    float saturationRate;
    Activity activity;
};

#endif // ANIMAL_H
