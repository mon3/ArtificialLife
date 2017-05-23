#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
#include "being.h"



class Animal : public Being
{
    Q_OBJECT
public:

    Animal(int _logX, int _logY) : Being(_logX, _logY) { activity = IDLE; }
    void action();
    virtual int type() const = 0;
    enum Activity {
        MATING,
        HUNTING, //for herbivorous ?
        IDLE,
//      RESTING,
//      SLEEPING,
//      NURSING, - for no need to nurse child
        RUNNNING_AWAY,
        DEAD
    };
    Q_ENUM(Activity)

    int getEveSight() const;

    float getSaturationRate() const;
    void setSaturationRate(float value);

    int getFoodCapacity() const;
    void setFoodCapacity(int value);

    float getMetabolism() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
signals:
    void callWindow(Being*);

protected:
    void move(int x = UNKNOWN_LOCATION, int y = UNKNOWN_LOCATION);

private:
    //subactions
    //set of subactions for every type of animal will be defined:
    virtual Being* hunt() = 0;
    virtual void eat(Being*) = 0;

    void mate(Animal&);
    void rest();
    void sleep();
    void run();




    int eveSight = 5;
    int age;
//  const int generation;
    int generation;
    int speed = 5;

    int foodCapacity;
    float metabolism;
    float exaustionLevel;
    float saturationRate;
    Activity activity;

//  for painter to define color
    virtual Qt::GlobalColor getPenColor() const = 0;

//  undefined grid location
    static const int UNKNOWN_LOCATION = -1;
};

#endif // ANIMAL_H
