#ifndef ANIMAL_H
#define ANIMAL_H

#include <QDebug>
#include "being.h"
#include <constrainedvalue.h>



class Animal : public Being
{
    Q_OBJECT
public:

    Animal(int _logX, int _logY) : Being(_logX, _logY) { }
//    Animal(int _logX, int _logY) : Being(_logX, _logY) { }
    ~Animal(){}
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

    void setFeaturesEA(QVector<int> vals);
    QVector<int> getFeaturesEA() const;

    void setFeaturesEA(QVector<int>& vals, Beings beingType);


    void displayStd() const;
    void displayFeatures() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
signals:
    void callWindow(Being*);

protected:
    void move(int x = UNKNOWN_LOCATION, int y = UNKNOWN_LOCATION);

private:
    //subactions
    //set of subactions for every type of animal will be defined:
//    virtual Being* hunt() = 0;
//    virtual void eat(Being*) = 0;

    void mate(Animal&);
    void rest();
    void sleep();
    void run();




    int eyeSight; // TO
    int age;
//    const int generation;
    int generation;
    int speed; // TO
//    int huntingPotential;


    int foodCapacity; // TO
    int metabolism; // TO
    int exhaustionLevel; // TO
    int saturationRate;
    Activity activity;

    QVector<int> featuresEA; //standard deviations for evolutionary algorithm
    QVector<double> stdDevs; //standard deviations for evolutionary algorithm

//  for painter to define color
    virtual Qt::GlobalColor getPenColor() const = 0;

//  undefined grid location
    static const int UNKNOWN_LOCATION = -1;
};

#endif // ANIMAL_H
