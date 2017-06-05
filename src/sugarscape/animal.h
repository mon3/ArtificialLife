#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
#include <functional>
#include "being.h"
#include "src/shared/board.h"
#include "src/evolalg/constrainedvalue.h"



class Animal : public Being
{
    Q_OBJECT
public:


    Animal(int _logX, int _logY) : Being(_logX, _logY) { activity = IDLE; setHitPoints(100); }
    ~Animal(){}
    void action();
    virtual int type() const = 0;

    enum Activity {
        MATING,
        HUNTING, //for herbivorous ?
        IDLE,
        RUNNNING_AWAY,
        DEAD
    };
    Q_ENUM(Activity)

    void setEyeSight(int value);
    int getEyeSight() const;

    void setAge(int value);
    int getAge() const;

    void setGeneration(int value);
    int getGeneration() const;

    void setSpeed(int value);
    int getSpeed() const;

    void setMetabolism(int value);
    int getMetabolism() const;

    void setFoodCapacity(int value);
    int getFoodCapacity() const;

    void setExhaustionLevel(int value);
    int getExhaustionLevel() const;

    void setSaturationRate(int value);
    int getSaturationRate() const;

    void setStdDevs(QVector<double> vals);
    QVector<double> getStdDevs() const;

    void setFeaturesEA(QVector<int>& vals, Beings type);
    QVector<int> getFeaturesEA() const;

    void displayStd() const;
    void displayFeatures() const;



    Activity getActivity() const;

    void setFeaturesEA(QVector<int> vals);
    virtual void accept(Visitor *) override = 0;
protected:
    void foodConsumptionRule(int& foodValue);

protected:

    //subactions
    //set of subactions for every type of animal will be defined:


    // TODO: consider to make a template function
    virtual Being* hunt() = 0;
    virtual void eat(Being*) = 0;
    virtual std::vector<Animal*> findEnemies() = 0;

private:
    void move(int x = UNKNOWN_LOCATION, int y = UNKNOWN_LOCATION);
    void moveClose(int goalX,int goalY);
    void mate(Animal*);


    void rest();
    void sleep();
    void runFrom(const std::vector<Animal*>& enemies);

    //routine functions, to simplify action()
    void huntRoutine();
    void enemiesHandlingRoutine();
    void foodConsumptionRoutine(ParametersSet*);
    void exaustionLevelHandlingRoutine(ParametersSet* set);



    int eyeSight = 5; // feature used in EA
    int age;
//  const int generation;
    int generation;
    int speed = 3; // feature used in EA
//    int huntingPotential;
    int foodCapacity; // feature used in EA
    int metabolism = 5; // feature used in EA
    int exhaustionLevel; // feature used in EA
    int saturationRate = 100; // feature used in EA

    Activity activity;

    QVector<int> featuresEA; //standard deviations for evolutionary algorithm
    QVector<double> stdDevs; //standard deviations for evolutionary algorithm


//  undefined grid location
    static const int UNKNOWN_LOCATION = -1;

    const static std::function<int(int)> direction;

    // Being interface

};

#endif // ANIMAL_H
