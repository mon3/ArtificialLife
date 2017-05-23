#ifndef PLANT_H
#define PLANT_H
#include "being.h"
#include <QDebug>
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

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PLANT_H
