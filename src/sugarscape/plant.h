#ifndef PLANT_H
#define PLANT_H
#include <QDebug>

#include "src/sugarscape/being.h"

/*!
 * \brief The Plant class - plant on board
 *
 * Passive; cannot be removed from the board
 *
 * \ingroup sugarscape
 */
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
