#include "grid.h"
#include <vector>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/irange.hpp>
#include <QVector>

#include <evolutionaryalg.h>

//// new individual will be added to Initial population
//void initializeIndividual(int X, int Y, Beings beingType, std::vector<Animal*>& IniPop)
//{
//    // possible solution: to tighten the boundaries for stddev
//    Generator genExh(ParametersSet::maxExhaustionLevel *0.5, (ParametersSet::maxExhaustionLevel-ParametersSet::minExhaustionLevel) * randomDouble(0.2, 0.8), ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
//    Generator genHitPts(ParametersSet::maxHitPoints *0.5, (ParametersSet::maxHitPoints - ParametersSet::minHitPoints) * randomDouble(0.2, 0.8), ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
//    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * randomDouble(0.3, 0.4), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);
//    Generator genAge((ParametersSet::maxAge - ParametersSet::minAge) *0.5,(ParametersSet::maxAge - ParametersSet::minAge) * randomDouble(0.2, 0.4), ParametersSet::minAge, ParametersSet::maxAge);

//    QVector<double> stdDevs;
//    stdDevs.push_back(genHitPts.getStddev());
//    stdDevs.push_back(genEye.getMean());
//    stdDevs.push_back(genAge.getMean());

////    qDebug() << "SIGMA: ";
////    qDebug() << "hitpts = " << genHitPts.getStddev();
////    qDebug() << "Eye = " << genEye.getStddev();
////    qDebug() << "Age = " << genAge.getStddev();


//    Being* being;


//    if (beingType == Beings::PREDATOR)
//    {
//        Generator genPredSpeed((ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * 0.5,(ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * randomDouble(0.3, 0.4), ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed);
//        Generator genPredFoodCap((ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * 0.5,(ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity);
//        Generator genPredMetabolism((ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * 0.5,(ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism);
//        Generator genPredSaturation((ParametersSet::maxPredatorSaturationRate - ParametersSet::minPredatorSaturationRate) * 0.5,(ParametersSet::maxPredatorSaturationRate - ParametersSet::minPredatorSaturationRate) * randomDouble(0.2, 0.4), ParametersSet::minPredatorSaturationRate, ParametersSet::maxPredatorSaturationRate);


//        stdDevs.push_back(genPredSpeed.getStddev());
//        stdDevs.push_back(genPredFoodCap.getStddev());
//        stdDevs.push_back(genPredMetabolism.getStddev());
//        stdDevs.push_back(genExh.getStddev());
//        stdDevs.push_back(genPredSaturation.getStddev());

////        qDebug() << "speed = " << genPredSpeed.getStddev();
////        qDebug() << "foodcap = " << genPredFoodCap.getStddev();
////        qDebug() << "metabolism = " << genPredMetabolism.getStddev();
////        qDebug() << "Exh = " << genExh.getStddev();
////        qDebug() << "saturation = " << genPredSaturation.getStddev();

////        qDebug() << "GEN hitpts = " << genHitPts();
////        qDebug() << "GEN Eye = " << genEye();
////        qDebug() << "GEN Age = " << genAge();



//        being = static_cast<Being*>(new Predator(X, Y,(int)round(genHitPts()), (int)round(genEye()), (int)round(genAge()), 1, (int)round(genPredSpeed()), (int)round(genPredFoodCap()), (int)round(genPredMetabolism()), (int)round(genExh()), (int)round(genPredSaturation()), stdDevs));

//    }
//    else if (beingType == Beings::HERBIVOROUS)
//    {
//        Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.5,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
//        Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.5,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
//        Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.5,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);
//        Generator genHerbSaturation((ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * 0.5,(ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSaturationRate, ParametersSet::maxHerbivorousSaturationRate);

//        stdDevs.push_back(genHerbSpeed.getStddev());
//        stdDevs.push_back(genHerbFoodCap.getStddev());
//        stdDevs.push_back(genHerbMetabolism.getStddev());
//        stdDevs.push_back(genExh.getStddev());
//        stdDevs.push_back(genHerbSaturation.getStddev());

///*        qDebug() << "speed = " << genHerbSpeed.getStddev();
//        qDebug() << "foodcap = " << genHerbFoodCap.getStddev();
//        qDebug() << "metabolism = " << genHerbMetabolism.getStddev();
//        qDebug() << "Exh = " << genExh.getStddev();
//        qDebug() << "saturation = " << genHerbSaturation.getStddev(); */

//        being = static_cast<Being*>(new Herbivorous(X, Y, (int)round(genHitPts()), (int)round(genEye()), (int)round(genAge()), 1, (int)round(genHerbSpeed()), (int)round(genHerbFoodCap()), (int)round(genHerbMetabolism()), (int)round(genExh()), (int)round(genHerbSaturation()), stdDevs));
//    }
//    else
//    {
//        qDebug() << "WRONG BEING TYPE PASSED AS VALUE! ";
//    }

//    IniPop.push_back(qobject_cast<Animal*>(being));
//}


//void initializePopulations(int N, std::vector<Animal*>& predatorIniPop, std::vector<Animal*>& herbivorousIniPop)
//{


//    // mu - size of the population
//    int mu = int(N * N * 0.2);
//    qDebug() << "Initial pop size: " << mu << endl;


//    std::vector<int> indicesX(N*N);
//    std::vector<int> indicesY(N*N);

//    generate(begin(indicesX), end(indicesX), rangegenerator(0));
//    generate(begin(indicesY), end(indicesY), rangegenerator(0));

//    random_shuffle(begin(indicesX), end(indicesX));
//    random_shuffle(begin(indicesY), end(indicesY));

////    Generator genExh(ParametersSet::maxExhaustionLevel *0.5, 30.0, ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
////    Generator genHitPts(ParametersSet::maxHitPoints *0.5, 25.0, ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
////    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.2, ParametersSet::minEyeSight, ParametersSet::maxEyeSight);
////    Generator genAge((ParametersSet::maxAge - ParametersSet::minAge) *0.5,(ParametersSet::maxAge - ParametersSet::minAge) *0.25, ParametersSet::minAge, ParametersSet::maxAge);

////    Generator genPredSpeed((ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * 0.6,(ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) *0.2, ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed);
////    Generator genPredFoodCap((ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * 0.6,(ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) *0.2, ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity);
////    Generator genPredMetabolism((ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * 0.6,(ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) *0.3, ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism);
////    Generator genPredSaturation((ParametersSet::maxPredatorSaturationRate - ParametersSet::minPredatorSaturationRate) * 0.6,(ParametersSet::maxPredatorSaturationRate - ParametersSet::minPredatorSaturationRate) *0.35, ParametersSet::minPredatorSaturationRate, ParametersSet::maxPredatorSaturationRate);

////    Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.6,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) *0.2, ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
////    Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.6,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) *0.2, ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
////    Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.6,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) *0.3, ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);
////    Generator genHerbSaturation((ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * 0.6,(ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) *0.35, ParametersSet::minHerbivorousSaturationRate, ParametersSet::maxHerbivorousSaturationRate);

////    qDebug() << "STD: " << genExh.getStddev();

////    Generator g(ParametersSet::maxExhaustionLevel *0.5, 30.0, ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
////    for (int i = 0; i < 10; i++)
////        qDebug() << g() << ' 'f;


//    for (int i=0; i< mu; ++i)
//    {
//        qDebug() << indicesX[i] << " " << indicesY[i] ;
//\
////        predatorIniPop.push_back(new Predator(indicesX[i], indicesY[i], random(ParametersSet::minHitPoints, ParametersSet::maxHitPoints),
////                                              random(ParametersSet::minEyeSight, ParametersSet::maxEyeSight),
////                                              random(ParametersSet::minAge, ParametersSet::maxAge), 1,
////                                              random(ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed),
////                                              random(ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity),
////                                              random(ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism),
////                                              random(ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel - 30),
////                                              random(ParametersSet::minPredatorSaturationRate, ParametersSet::maxPredatorSaturationRate)));

////        QVector<float> stdDevs;
////        stdDevs.push_back(genHitPts.getStddev());
////        stdDevs.push_back(genEye.getMean());
////        stdDevs.push_back(genAge.getMean());
////        stdDevs.push_back(genPredSpeed.getMean());
////        stdDevs.push_back(genPredFoodCap.getStddev());
////        stdDevs.push_back(genPredMetabolism.getStddev());
////        stdDevs.push_back(genExh.getStddev());
////        stdDevs.push_back(genPredSaturation.getStddev());

//        initializeIndividual(indicesX[i], indicesY[i], Beings::PREDATOR, predatorIniPop);
//        initializeIndividual(indicesX[i+2], indicesY[i+2], Beings::HERBIVOROUS, herbivorousIniPop);

////        predatorIniPop.push_back(new Predator(indicesX[i], indicesY[i], genHitPts(), genEye(), genAge(), 1, genPredSpeed(),
////                                              genPredFoodCap(), genPredMetabolism(), genExh(), genPredSaturation(),stdDevs));

////        herbivorousIniPop.push_back(new Herbivorous(indicesX[i+2], indicesY[i+2], random(ParametersSet::minHitPoints, ParametersSet::maxHitPoints),
////                random(ParametersSet::minEyeSight, ParametersSet::maxEyeSight),
////                random(ParametersSet::minAge, ParametersSet::maxAge),1,
////                random(ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed),
////                random(ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity),
////                random(ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism),
////                random(ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel - 30),
////                random(ParametersSet::minHerbivorousSaturationRate, ParametersSet::maxHerbivorousSaturationRate)));
////        qDebug() << indicesX[i+2] << " " << indicesY[i+2] ;

//    }

////    boost::push_back(availableGridElementsY, boost::irange(1, N*N+1));
////    for (int i=0; i<= mu; ++i)
////    {
////      int currX = rand() % availableGridElementsX.size();
////      int currY = rand() % availableGridElementsX.size();
////      predatorIniPop.push_back(newPredator(availableGridElementsX(currX), availableGridElementsY(currY)));
////      availableGridElementsX.erase(currX);
////      availableGridElementsY.erase(currY);
////      qDebug() << rand() % availableGridElementsX.size() << ' ';
////    }

//    for (auto i = availableGridElements.begin(); i != availableGridElements.end(); ++i)
//        qDebug() << *i << ' ';

//}

Grid::Grid()
{
//    EvolutionaryAlg* ea = new EvolutionaryAlg();
    this->setEA(new EvolutionaryAlg());
    QVector<Animal*> predatorIniPop;
    QVector<Animal*> herbivorousIniPop;
    ParametersSet* set = ParametersSet::getInstance();
    EA->initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop);
//    qDebug() << "TEST: " << static_cast<Being*>(predatorIniPop[20])->getLogX()<< " " <<static_cast<Being*>(predatorIniPop[20])->getLogY();
//    int mu = int(set->getGridSize() * set->getGridSize() * 0.2);

    QVector<Animal*> predatorTempPop;
    QVector<Animal*> herbivorousTempPop;
    int lambda = 30;
    qDebug() << "Predator Temp pop generation..." ;
    predatorTempPop = EA->generateTemporaryPopulation(lambda, predatorIniPop);
    qDebug() << "Herbivorous Temp pop generation..." ;
    herbivorousTempPop = EA->generateTemporaryPopulation(lambda, herbivorousIniPop);

//    qDebug() << "PREDATOR TEMP POP FEATURES SIZE = " << predatorTempPop.at(0)->getFeaturesEA().size();

    EA->reproducePopulation(predatorTempPop, 2);
    EA->mutation(predatorTempPop);

    qDebug() << "Temp size: " << (predatorTempPop.at(0)->getStdDevs()).size();
    qDebug() << "Temp size: " << (predatorTempPop.at(1)->getStdDevs()).size();
    qDebug() << "Temp size: " << (predatorTempPop.at(2)->getStdDevs()).size();

    qDebug() << "Temp size: " << predatorTempPop.size();

    for (int i=0; i< predatorIniPop.size(); ++i)
    {
        addItem(predatorIniPop[i]);
        connect(predatorIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
        // TODO:: add paint functions to visualize initial populations
        addItem(herbivorousIniPop[i]);
        connect(herbivorousIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));

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
