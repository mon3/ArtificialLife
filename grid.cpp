#include "grid.h"
#include <vector>

#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/irange.hpp>
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


void initializePopulations(int N, std::vector<Animal*>& predatorIniPop, std::vector<Animal*>& herbivorousIniPop)
{
//    std::vector<Animal*> predatorIniPop;
//    std::vector<Animal*> herbivorousIniPop;

    int initialPopSize = int(N * N * 0.2);
    qDebug() << "Initial pop size: " << initialPopSize << endl;



    // vector representing grid
//    std::vector<int> availableGridElementsX;
//    boost::push_back(availableGridElementsX, boost::irange(1, N*N+1));

    std::vector<int> indicesX(N*N);
    std::vector<int> indicesY(N*N);

    generate(begin(indicesX), end(indicesX), rangegenerator(0));
    generate(begin(indicesY), end(indicesY), rangegenerator(0));

    random_shuffle(begin(indicesX), end(indicesX));
    random_shuffle(begin(indicesY), end(indicesY));

//    for (auto i= indices.begin(); i != indices.end(); ++i)
//    {
//        qDebug() << *i << ' ';
//    }

//    qDebug() << "Indices size: " << indicesX.size();

    for (int i=0; i< initialPopSize; ++i)
    {
        predatorIniPop.push_back(new Predator(indicesX[i], indicesY[i]));
//        qDebug() << indicesX[i] << " " << indicesY[i] ;


        herbivorousIniPop.push_back(new Predator(indicesX[i+2], indicesY[i+2]));
//        qDebug() << indicesX[i+2] << " " << indicesY[i+2] ;

    }

//    boost::push_back(availableGridElementsY, boost::irange(1, N*N+1));
//    for (int i=0; i<= initialPopSize; ++i)
//    {
//      int currX = rand() % availableGridElementsX.size();
//      int currY = rand() % availableGridElementsX.size();
//      predatorIniPop.push_back(newPredator(availableGridElementsX(currX), availableGridElementsY(currY)));
//      availableGridElementsX.erase(currX);
//      availableGridElementsY.erase(currY);
//      qDebug() << rand() % availableGridElementsX.size() << ' ';
//    }

//    for (auto i = availableGridElements.begin(); i != availableGridElements.end(); ++i)
//        qDebug() << *i << ' ';

}

Grid::Grid()
{

//    std::vector<Animal*> predatorIniPop;
//    std::vector<Animal*> herbivorousIniPop;
//    ParametersSet* set = ParametersSet::getInstance();
//    initializePopulations(set->getGridSize(), predatorIniPop, herbivorousIniPop);
//    qDebug() << "TEST: " << static_cast<Being*>(predatorIniPop[20])->getLogX()<< " " <<static_cast<Being*>(predatorIniPop[20])->getLogY();
//    int initialPopSize = int(set->getGridSize() * set->getGridSize() * 0.2);


//    for (int i=0; i< predatorIniPop.size(); ++i)
//    {
//        addItem(predatorIniPop[i]);
//        connect(predatorIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));
//        // TODO:: add paint functions to visualize initial populations
//        addItem(herbivorousIniPop[i]);
//        connect(herbivorousIniPop[i], SIGNAL(callWindow(Being*)), set, SLOT(callWindow(Being*)));

//    }



//    int initialPopSize = int((ParametersSet::getInstance()->getGridSize())*(ParametersSet::getInstance()->getGridSize())*0.2);
//    qDebug() << "Initial pop size: " << initialPopSize << endl;

//    for (int i=0; i<= initialPopSize; ++i)
//    {
//        predatorIniPop.push_back(new Predator(random(1, ParametersSet::getInstance()->getGridSize()),random(1, ParametersSet::getInstance()->getGridSize())));
//        herbivorousIniPop.push_back(new Herbivorous(random(1, ParametersSet::getInstance()->getGridSize()),random(1, ParametersSet::getInstance()->getGridSize())));

//    }

//    addItem();

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
    //not rightt!
//    foreach (QGraphicsItem* item, list) {

//        Being* b = static_cast< Being* >(item);
//        if(b == nullptr) {
//            qDebug() << "line";
//            continue;
//        }
//        b->action();
//        b->setPos((b->getLogX() * ParametersSet::SCENE_WIDTH) / set->getGridSize(),
//                    (b->getLogY() * ParametersSet::SCENE_WIDTH) / set->getGridSize());
//    }

}
