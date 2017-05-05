#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
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
    Q_OBJECT
public:

    Animal(int _logX, int _logY) : Being(_logX, _logY) { }
    void action();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
signals:
    void callWindow(Being*);
private:
    //subactions
    //set of subactions for every type of animal will be defined:
//    virtual void hunt(Being& )=0;



    void mate(Animal&);
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

    virtual Qt::GlobalColor getPenColor() const = 0;

};

#endif // ANIMAL_H
