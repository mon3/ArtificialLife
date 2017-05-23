#ifndef PLANT_H
#define PLANT_H
#include "being.h"

class Plant : public Being
{
    Q_OBJECT
public:
    Plant(int _logX, int _logY) : Being(_logX, _logY) { }

    void action();
    int type() const { return Beings::PLANT; }

    // Being interface
private:
    Qt::GlobalColor getPenColor() const override;
};

#endif // PLANT_H
