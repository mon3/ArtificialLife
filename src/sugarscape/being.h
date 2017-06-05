#ifndef BEING_H
#define BEING_H

#include <QObject>
#include "src/shared/parametersset.h"
#include "src/view/visitor.h"

class Being : public QObject
{
    Q_OBJECT
public:
    Being(int _logX, int _logY);
    int getHitPoints() const;
    void setHitPoints(int value);

    int getLogX() const;
    void setLogX(int value);

    int getLogY() const;
    void setLogY(int value);

    virtual void action() = 0;
    virtual  int type() const = 0 ;
    virtual void accept(Visitor*) = 0;
    bool getIsDead() const;

protected:
    void setIsDead();
private:
    bool isDead;
    int logX;
    int logY;
    int hitPoints;
};

#endif // BEING_H
