#include "grid.h"

Grid::Grid()
{
    //test subjects
    Animal* ex = new Predator(5, 5);
    addItem(ex);
    ParametersSet* set = ParametersSet::getInstance();
    connect(ex, SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
    ex = new Herbivorous(10, 10);
    addItem(ex);
    connect(ex, SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
}

void Grid::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    const int gridNumber = ParametersSet::getInstance()->getGridSize();
    int x = 0, y = 0;
    const int distance = ParametersSet::SCENE_WIDTH / gridNumber;
    for (int i = -1; i < gridNumber; ++i ) {
        painter->setPen(Qt::red);
        painter->drawLine(QLineF(x,0,x,ParametersSet::SCENE_WIDTH));
        painter->setPen(Qt::green);
        painter->drawLine(QLineF(0,y,ParametersSet::SCENE_WIDTH,y));
        x+= distance;
        y+= distance;
    }
}

void Grid::updateGrid()
{
    QList<QGraphicsItem*> list = this->items();
    // TODO: better mapping
    ParametersSet* set = ParametersSet::getInstance();
    foreach (QGraphicsItem* item, list) {
        Being* var = static_cast<Being*>(item);

        //not safe! do qcast later
        Animal* a = static_cast<Animal*>(var);
        a->action();
        var->setPos((var->getLogX() * ParametersSet::SCENE_WIDTH) / set->getGridSize(),
                    (var->getLogY() * ParametersSet::SCENE_WIDTH) / set->getGridSize());
    }

}
