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



//Grid::Grid()
//{
//    this->setEA(new EvolutionaryAlg());
//    QVector<std::shared_ptr<Animal>> predatorIniPop;
//    QVector<std::shared_ptr<Animal>> herbivorousIniPop;
//    ParametersSet* set = ParametersSet::getInstance();
//    int mu = 50;
//    int lambda = 80;
//    int iters = 100;
//    EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop, mu);
//    EA->runEA(mu, lambda, iters, 0, predatorIniPop, herbivorousIniPop);

//    EA->printPopulation(predatorIniPop);
//    this->updateGrid();
//}



Grid::Grid(EvolutionaryAlg *ea, const int &maxTicks, const int& gridSize) :
    maxTicks(maxTicks), ticks(0)
{
    algorithm = std::unique_ptr<EvolutionaryAlg>(ea);
    window =std::unique_ptr<BeingWindow>(new BeingWindow());
    ParametersSet* set = ParametersSet::getInstance(gridSize);
    Board* board = Board::getInstance(gridSize);

    lambdaAdd = [&] (BeingItem* b) -> void {
         connect(b, SIGNAL(callWindow(Being*)), this, SLOT(callWindow(Being*)));
         connect(this, SIGNAL(updateBeings()), b, SLOT(updateBeing()));
         this->addItem(b);
    };
    Populations population;
    (*algorithm).initializePopulations(gridSize,std::get<0>(population), std::get<1>(population), 10);
    board->setCurrentPopulationOnBoard(population);
    std::for_each(std::begin(std::get<0>(population)), std::end(std::get<0>(population))
                  , [&](std::shared_ptr<Animal>& a) -> void {
        lambdaAdd(new BeingItem(std::dynamic_pointer_cast<Being>(a)));
    });
    std::for_each(std::begin(std::get<1>(population)), std::end(std::get<1>(population))
                  , [&](std::shared_ptr<Animal>& a) -> void {
        lambdaAdd(new BeingItem(std::dynamic_pointer_cast<Being>(a)));
    });
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

void Grid::callWindow(Being * b)
{
    if(!window->isVisible()) {
        window->initWindow(b);
        window->show();
    }

}

void Grid::updateGrid()
{    
    emit updateBeings();
    if(ticks++ > maxTicks) {
        ticks = 0;
        Board* b = Board::getInstance();
        Populations& currentPopulation = b->getCurrentPopulation();
        qDebug() << "pop: p - " << std::get<0>(currentPopulation).size() << " h - " << std::get<1>(currentPopulation).size();
        algorithm->runEA(20, 40, 1, 0, std::get<1>(currentPopulation), std::get<0>(currentPopulation));
        qDebug() << "after: p - " << std::get<0>(currentPopulation).size() << " h - " << std::get<1>(currentPopulation).size();
        std::for_each(std::begin(std::get<0>(currentPopulation)),std::end(std::get<0>(currentPopulation))
                      ,[&](std::shared_ptr<Animal>& a) -> void {
               if(b->isFreeCell(a->getLogX(), a->getLogY())) {
                   b->addBeing(a.get());
                   lambdaAdd(new BeingItem(std::dynamic_pointer_cast<Being>(a)));
               }

        });

        std::for_each(std::begin(std::get<1>(currentPopulation)),std::end(std::get<1>(currentPopulation))
                      ,[&](std::shared_ptr<Animal>& a) -> void {
               if(b->isFreeCell(a->getLogX(), a->getLogY())) {
                   b->addBeing(a.get());
                   lambdaAdd(new BeingItem(std::dynamic_pointer_cast<Being>(a)));
               }

        });

    }

}

