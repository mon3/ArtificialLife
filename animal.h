#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
#include <functional>
#include "being.h"



class Animal : public Being
{
    Q_OBJECT
public:

    Animal(int _logX, int _logY) : Being(_logX, _logY) { activity = IDLE; setHitPoints(100); }
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

    int getSaturationRate() const;
    void setSaturationRate(int value);

    int getFoodCapacity() const;
    void setFoodCapacity(int value);

    int getMetabolism() const;

    int getSpeed() const;
    void setSpeed(int value);

    Activity getActivity() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void foodConsumptionRule(int& foodValue);
signals:
    void callWindow(Being*);

protected:

    //subactions
    //set of subactions for every type of animal will be defined:

    // TODO: consider to make a template function
    virtual Being* hunt() = 0;
    virtual void eat(Being*) = 0;
    virtual vector<Animal*> findEnemies() = 0;

private:
    void move(int x = UNKNOWN_LOCATION, int y = UNKNOWN_LOCATION);
    void moveClose(int goalX,int goalY);
    void mate(Animal*);

    void rest();
    void sleep();
    void runFrom(const vector<Animal*>& enemies);

    //routine functions, to simplify action()
    void huntRoutine(ParametersSet*);
    void enemiesHandlingRoutine();
    void foodConsumptionRoutine(ParametersSet*);
    void exaustionLevelHandlingRoutine(ParametersSet* set);


    int eveSight = 5;
    int age;
//  const int generation;
    int generation;
    int speed = 5;

    int foodCapacity;
    int metabolism = 3;
    int exaustionLevel;
    int saturationRate = 100;
    Activity activity;

//  for painter to define color
    virtual Qt::GlobalColor getPenColor() const = 0;

//  undefined grid location
    static const int UNKNOWN_LOCATION = -1;

    const static function<int(int)> direction;
};

#endif // ANIMAL_H
