#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
#include "being.h"



class Animal : public Being
{
    Q_OBJECT
public:

    Animal(int _logX, int _logY) : Being(_logX, _logY) { }
    void action();
    virtual int type() const = 0;
    enum Activity {
        MATING,
        HUNTING, //for herbivorous ?
//      RESTING,
//      SLEEPING,
//      NURSING, - for no need to nurse child
        RUNNNING_AWAY,
        DEAD
    };
    Q_ENUM(Activity)

    int getEveSight() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
signals:
    void callWindow(Being*);
private:
    //subactions
    //set of subactions for every type of animal will be defined:
    virtual void hunt()=0;


    void move();
    void mate(Animal&);
    void eat(Being&);
    void rest();
    void sleep();
    void run();


    int eveSight;
    int age;
//    const int generation;
    int generation;
    int speed;


    int food_capacity;
    float metabolism;
    float exaustionLevel;
    float saturationRate;
    Activity activity;

//  for painter to define color
    virtual Qt::GlobalColor getPenColor() const = 0;

};

#endif // ANIMAL_H
