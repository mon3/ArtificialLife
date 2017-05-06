#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include <QPainter>
#include "parametersset.h"
#include "predator.h"
#include "herbivorous.h"
#include "plant.h"

#include <QDebug>

class Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    Grid();
    ~Grid() {}
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
private:

public slots:
    void updateGrid();
};

#endif // GRID_H
