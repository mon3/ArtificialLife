#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
<<<<<<< HEAD
#include <QPainter>
#include "parametersset.h"
#include <QDebug>
=======
#include "parametersset.h"
>>>>>>> multi_dev

class Grid : public QGraphicsScene
{
public:
<<<<<<< HEAD
    Grid(ParametersSet* _set) : set(_set) { }
    ~Grid() { delete set; }
private:

    //todo smart pointers
    ParametersSet* set;
=======
    Grid(ParametersSet&);

private:
    ParametersSet& set;
>>>>>>> multi_dev
};

#endif // GRID_H
