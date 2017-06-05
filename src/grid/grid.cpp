#include "grid.h"
#include <vector>

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/irange.hpp>
#include <QVector>

// use "" to include yours file, <> for standard libraries
#include "src/evolalg/evolutionaryalg.h"
#include <QGraphicsItem>

int random(int min, int max) //range : [min, max)
{
   static bool first = true;
   if ( first )
   {
      //srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min);
}


struct rangegenerator {
    rangegenerator(int init) : start(init) { }

    int operator()() {
        return start++;
    }

    int start;
};



Grid::Grid()
{
    this->setEA(new EvolutionaryAlg());
    QVector<std::shared_ptr<Animal>> predatorIniPop;
    QVector<std::shared_ptr<Animal>> herbivorousIniPop;
    ParametersSet* set = ParametersSet::getInstance();
    int mu = 50;
    int lambda = 80;
    int iters = 100;
    EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop, mu);
    EA->runEA(mu, lambda, iters, 0, predatorIniPop, herbivorousIniPop);

    EA->printPopulation(predatorIniPop);
    this->updateGrid();
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

}


void Grid::setEA(EvolutionaryAlg* ea)
{
    EA = ea;
}

EvolutionaryAlg* Grid::getEA() const
{
    return EA;
}
