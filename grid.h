#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include <QPainter>
#include "parametersset.h"
#include "being.h"
#include "animal.h"
#include <QDebug>

class Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    Grid(ParametersSet* _set) : set(_set) { }
    ~Grid() { delete set; }
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:

    //todo smart pointers
    ParametersSet* set;
public slots:
    void updateGrid();
};

#endif // GRID_H
