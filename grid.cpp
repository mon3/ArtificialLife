#include "grid.h"


void Grid::drawBackground(QPainter *painter, const QRectF &rect)
{
    const int gridNumber = 20;
    int x = 0, y = 0;
    painter->drawLine(5, 5, 10, 10);
    qDebug() << painter->viewport() << " sc: " <<this->itemsBoundingRect();
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
    foreach (QGraphicsItem* item, list) {
        Being* var = static_cast<Being*>(item);
        var->setPos((var->getLogX() * ParametersSet::SCENE_WIDTH) / set->getGridSize(),
                    (var->getLogY() * ParametersSet::SCENE_WIDTH) / set->getGridSize());
    }

}
