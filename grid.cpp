#include "grid.h"
#include <vector>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/irange.hpp>
#include <QVector>

#include <evolutionaryalg.h>



Grid::Grid()
{
    this->setEA(new EvolutionaryAlg());
    QVector<Animal*> predatorIniPop;
    QVector<Animal*> herbivorousIniPop;
    ParametersSet* set = ParametersSet::getInstance();
    EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop);

    QVector<Animal*> predatorTempPop;
    QVector<Animal*> herbivorousTempPop;
    QVector<Animal*> predParentsChildrenPop = predatorIniPop;
    QVector<Animal*> herbParentsChildrenPop = herbivorousIniPop;
    int lambda = 80;
    for (int i=0; i<500; ++i)
    {

    qDebug() << "parent size = " << predParentsChildrenPop.size();
//    qDebug() << "Predator Temp pop generation..." ;
    predatorTempPop = EA->generateTemporaryPopulation(lambda, predParentsChildrenPop);
//    qDebug() << "Herbivorous Temp pop generation..." ;
    herbivorousTempPop = EA->generateTemporaryPopulation(lambda, herbParentsChildrenPop);

//    qDebug() << "temp size = " << predatorTempPop.size();

    EA->reproducePopulation(predatorTempPop, 1);
//    qDebug() << "temp size after reproduce = " << predatorTempPop.size();

    EA->mutation(predatorTempPop);

//    qDebug() << "temp size after mutation = " << predatorTempPop.size();

    EA->reproducePopulation(herbivorousTempPop, 1);
    EA->mutation(herbivorousTempPop);

//    predParentsChildrenPop.clear();
//    herbParentsChildrenPop.clear();
    predParentsChildrenPop = predParentsChildrenPop + predatorTempPop;
    herbParentsChildrenPop = herbParentsChildrenPop +  herbivorousTempPop;

//    qDebug() << "par+child  = " << predParentsChildrenPop.size();

    predatorTempPop.clear();
    herbivorousTempPop.clear();

    int mi = 50;
    EA->selectMiBest(mi, predParentsChildrenPop);
    EA->selectMiBest(mi, herbParentsChildrenPop);

//    qDebug() << "mi selection  = " << predParentsChildrenPop.size();

    }

    qDebug()<<"GRID ... ";
//    qDebug() << "SIZE ..." << predParentsChildrenPop.size();
    qDebug() << "PREDATOR AFTER 50 ITERS...";
    EA->printPopulation(predParentsChildrenPop);

    QVector<std::pair<Animal*, double>> indivFitness;


    for (auto &indiv: predParentsChildrenPop )
    {
        indivFitness.push_back(std::make_pair(indiv, EA->fitnessFunction(EA->featuresToChromosome(indiv))));
    }

//    std::sort(indivFitness.begin(), indivFitness.end(), EA->sort_pair_second<Animal*, double>());

    qDebug() << "FINAL POPULATION SIZE = " << predParentsChildrenPop.size();

    for (unsigned i = 0; i< indivFitness.size(); ++i)
    {
        qDebug() << "FITNESS = " << indivFitness[i].second ;
    }
//    qDebug() << "HERBIVOROUS AFTER 50 ITERS...";
//    EA->printPopulation(herbParentsChildrenPop);

    for (int i=0; i< predParentsChildrenPop.size(); ++i)
    {
        addItem(predParentsChildrenPop[i]);
        connect(predParentsChildrenPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
        // TODO:: add paint functions to visualize initial populations
        addItem(herbParentsChildrenPop[i]);
        connect(herbParentsChildrenPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));

    }

    this->updateGrid();

//    QList<QGraphicsItem*> list = this->items();
//    // TODO: better mapping
//    int i =0 ;
//    foreach (QGraphicsItem* item, list) {
//        qDebug() << ++i;
//        Being* var = static_cast<Being*>(item);
//        var->paint(this->activeWindow()->pa);
//}
//    int mu = int((ParametersSet::getInstance()->getGridSize())*(ParametersSet::getInstance()->getGridSize())*0.2);
//    qDebug() << "Initial pop size: " << mu << endl;

//    for (int i=0; i<= mu; ++i)
//    {
//        predatorIniPop.push_back(new Predator(random(1, ParametersSet::getInstance()->getGridSize()),random(1, ParametersSet::getInstance()->getGridSize())));
//        herbivorousIniPop.push_back(new Herbivorous(random(1, ParametersSet::getInstance()->getGridSize()),random(1, ParametersSet::getInstance()->getGridSize())));

//    }

//    addItem();

   //test subjects
//    Animal* ex = new Predator(5, 5);
//    addItem(ex);
//    connect(ex, SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
//    ex = new Herbivorous(10, 10);
//    addItem(ex);
//    connect(ex, SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
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
        Being* var = static_cast<Being*>(item);

        //not safe! do qcast later
        Animal* a = qobject_cast<Animal*>(var);
        QVector<int> res = EA->featuresToChromosome(a);
        double fitness =  EA->fitnessFunction(res);

//        qDebug() <<"Type: " <<a->type();
//        qDebug() << "Size: " << res.size();

        for (const int& i : res) // access by const reference
        {
//                qDebug() << i << ' ';
//            qDebug() << i ;


        }
//        qDebug() << '\n';

//        a->action();
        var->setPos((var->getLogX() * ParametersSet::SCENE_WIDTH) / set->getGridSize(),
                    (var->getLogY() * ParametersSet::SCENE_WIDTH) / set->getGridSize());
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
