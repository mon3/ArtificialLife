#ifndef PLANT_H
#define PLANT_H
#include <QDebug>

#include "src/sugarscape/being.h"


class Plant : public Being
{
    Q_OBJECT
public:
    Plant(int _logX, int _logY) : Being(_logX, _logY) { setHitPoints(100); }

    void action();
    int type() const { return Beings::PLANT; }

    // Being interface
protected:
    void accept(Visitor *) override;
};

#endif // PLANT_H
