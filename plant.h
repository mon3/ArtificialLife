#ifndef PLANT_H
#define PLANT_H
#include "being.h"

class Plant : public Being
{
    Q_OBJECT
public:
    Plant();
    int type() const { return Beings::PLANT; }
};

#endif // PLANT_H
