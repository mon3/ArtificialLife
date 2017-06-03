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
    QVector<Animal*> predatorIniPop;
    QVector<Animal*> herbivorousIniPop;
    ParametersSet* set = ParametersSet::getInstance();
    EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop);
//    EA->runEA(50, 80, 500, 1, predatorIniPop, herbivorousIniPop);

//    qDebug()<<"GRID ... ";
////    qDebug() << "SIZE ..." << predParentsChildrenPop.size();
//    qDebug() << "PREDATOR FROM EA...";
//    EA->printPopulation(predatorIniPop);
//    EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop);
//    EA->runEA(50, 80, 500, 1, predatorIniPop, herbivorousIniPop);

//    qDebug()<<"GRID ... ";
////    qDebug() << "SIZE ..." << predParentsChildrenPop.size();
//    qDebug() << "PREDATOR FROM EA...";
//    EA->printPopulation(predatorIniPop);

//    QVector<std::pair<Animal*, double>> indivFitness;


//    for (auto &indiv: predatorIniPop)
//    {
//        indivFitness.push_back(std::make_pair(indiv, EA->fitnessFunction(EA->featuresToChromosome(indiv))));
//    }

//    std::sort(indivFitness.begin(), indivFitness.end(), EA->sort_pair_second<Animal*, double>());

//    qDebug() << "FINAL POPULATION SIZE = " << predatorIniPop.size();

//    for (unsigned i = 0; i< indivFitness.size(); ++i)
//    {
//        qDebug() << "FITNESS = " << indivFitness[i].second ;
//    }  EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop);
//    EA->runEA(50, 80, 500, 1, predatorIniPop, herbivorousIniPop);

//    qDebug()<<"GRID ... ";
////    qDebug() << "SIZE ..." << predParentsChildrenPop.size();
//    qDebug() << "PREDATOR FROM EA...";
//    EA->printPopulation(predatorIniPop);

//    QVector<std::pair<Animal*, double>> indivFitness;


//    for (auto &indiv: predatorIniPop)
//    {
//        indivFitness.push_back(std::make_pair(indiv, EA->fitnessFunction(EA->featuresToChromosome(indiv))));
//    }

////    std::sort(indivFitness.begin(), indivFitness.end(), EA->sort_pair_second<Animal*, double>());

//    qDebug() << "FINAL POPULATION SIZE = " << predatorIniPop.size();

//    for (unsigned i = 0; i< indivFitness.size(); ++i)
//    {
//        qDebug() << "FITNESS = " << indivFitness[i].second ;
//    }
////    qDebug() << "HERBIVOROUS AFTER 50 ITERS...";
////    EA->printPopulation(herbParentsChildrenPop);

//    for (int i=0; i< predatorIniPop.size(); ++i)
//    {
//        addItem(predatorIniPop[i]);
//        connect(predatorIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
//        // TODO:: add paint functions to visualize initial populations
//        addItem(herbivorousIniPop[i]);
//        connect(herbivorousIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));

//    }
////    qDebug() << "HERBIVOROUS AFTER 50 ITERS...";
////    EA->printPopulation(herbParentsChildrenPop);

//    for (int i=0; i< predatorIniPop.size(); ++i)
//    {
//        addItem(predatorIniPop[i]);
//        connect(predatorIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
//        // TODO:: add paint functions to visualize initial populations
//        addItem(herbivorousIniPop[i]);
//        connect(herbivorousIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));

//    }
//    QVector<std::pair<Animal*, double>> indivFitness;


//    for (auto &indiv: predatorIniPop)
//    {
//        indivFitness.push_back(std::make_pair(indiv, EA->fitnessFunction(EA->featuresToChromosome(indiv))));
//    }

////    std::sort(indivFitness.begin(), indivFitness.end(), EA->sort_pair_second<Animal*, double>());

//    qDebug() << "FINAL POPULATION SIZE = " << predatorIniPop.size();

//    for (unsigned i = 0; i< indivFitness.size(); ++i)
//    {
//        qDebug() << "FITNESS = " << indivFitness[i].second ;
//    }
////    qDebug() << "HERBIVOROUS AFTER 50 ITERS...";
////    EA->printPopulation(herbParentsChildrenPop);

//    for (int i=0; i< predatorIniPop.size(); ++i)
//    {
//        addItem(predatorIniPop[i]);
//        connect(predatorIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
//        // TODO:: add paint functions to visualize initial populations
//        addItem(herbivorousIniPop[i]);
//        connect(herbivorousIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));

//    }

    this->updateGrid();

}


//void Grid::drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget)
//{
//    QList<QGraphicsItem*> list = this->items();
//    QVector<QGraphicsItem*> vector; //I also tried QVector<int>vectorA(100);

//    vector = QVector<QGraphicsItem*>::fromList(list);
//    items =  &vector[0];

//    // TODO: better mapping￼
//    for (int i=0; i< list.size(); ++i)
//    {
//         Being* var = static_cast<Being*>(items[i]);
//         var->paint(painter);
//    }
////    int i =0 ;
////    foreach (QGraphicsItem* item, list) {
////        Being* var = static_cast<Being*>(item);
////        var -> paint(painter,options[i], widget );
////        qDebug() << ++i;

////}
//}

//void Grid::drawForeground(QPainter *painter, const QRectF &rect)
//{
//    QList<QGraphicsItem*> list = this->items();
//    qDebug() <<"List size: " << list.size();

////    int i =0 ;
//    foreach (QGraphicsItem* item, list) {
//        Being* var = static_cast<Being*>(item);
//        var -> paint(painter);
////        qDebug() << ++i;

//}
//}

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
    int i =0 ;
    foreach (QGraphicsItem* item, list) {
//        qDebug() << ++i;


        //not safe! do qcast later
//        Animal* a = qobject_cast<Animal*>(var);
//        QVector<int> res = EA->featuresToChromosome(a);
//        double fitness =  EA->fitnessFunction(res);

//        qDebug() <<"Type: " <<a->type();
//        qDebug() << "Size: " << res.size();

//        for (const int& i : res) // access by const reference
//        {
////                qDebug() << i << ' ';
////            qDebug() << i ;


//        }
//        qDebug() << '\n';

//        a->action();

    }


}


void Grid::setEA(EvolutionaryAlg* ea)
{
    EA = ea;
}

EvolutionaryAlg* Grid::getEA() const
{
    return EA;
}
