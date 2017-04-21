#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include "parametersset.h"

class Grid : public QGraphicsScene
{
public:
    Grid(ParametersSet&);

private:
    ParametersSet& set;
};

#endif // GRID_H
