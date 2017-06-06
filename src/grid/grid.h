#ifndef GRID_H
#define GRID_H

#include <QGraphicsScene>
#include <QPainter>

#include <QObject>
#include "src/shared/parametersset.h"
#include "src/grid/beingitem.h"
#include "src/grid/beingwindow.h"
#include <memory>
#include <QDebug>
#include <QPainter>

#include "src/evolalg/evolutionaryalg.h"

class Grid : public QGraphicsScene
{
    Q_OBJECT
public:
    ~Grid() {}

    Grid(EvolutionaryAlg *ea, const int &ticks, const int &gridSize);
protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    std::unique_ptr<EvolutionaryAlg> algorithm;
    int ticks;
    const int maxTicks;
    std::function<void(BeingItem*)> lambdaAdd;
    std::unique_ptr<BeingWindow> window;
public slots:
    void callWindow(Being* b);
    void updateGrid();
signals:
    void updateBeings();
};

#endif // GRID_H
