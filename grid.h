#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include <QPainter>

#include <QObject>
#include "parametersset.h"
#include "predator.h"
#include "herbivorous.h"
#include "plant.h"

#include <QDebug>
#include <QPainter>
#include <evolutionaryalg.h>

class Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    Grid();
    ~Grid() {}

    void setEA(EvolutionaryAlg* ea);
    EvolutionaryAlg* getEA() const;

//    void setGridPainter(QPainter *painter) {gridPainter = painter;}
//    QPainter* getGridPainter(){return gridPainter;}
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
//    void drawForeground(QPainter *painter, const QRectF &rect);

//    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget);
private:
//    QPainter *gridPainter;

    // maybe pointer to the object?
    EvolutionaryAlg* EA;
public slots:
    void updateGrid();
};

#endif // GRID_H
