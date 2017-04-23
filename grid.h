#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include <QPainter>
#include "parametersset.h"
#include <QDebug>

class Grid : public QGraphicsScene
{
public:
    Grid(ParametersSet* _set) : set(_set) { }
    ~Grid() { delete set; }
private:

    //todo smart pointers
    ParametersSet* set;
};

#endif // GRID_H
