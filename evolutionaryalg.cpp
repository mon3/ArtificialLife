#include "evolutionaryalg.h"

#include <QVector>
#include <QDebug>
#include <being.h>
#include <random>
#include <predator.h>
#include <herbivorous.h>
#include <algorithm>
#include <boost/lambda/lambda.hpp>


EvolutionaryAlg::EvolutionaryAlg()
{
      qDebug() << "EA Constructor. " ;
}

// parametry do algorytmu
double EvolutionaryAlg::fitnessFunction(QVector<int> chromosome)
{
    double fitness;

    fitness += (chromosome.at(0)*ParametersSet::eyeSightCoeff);
    fitness += (chromosome.at(1)*ParametersSet::speedCoeff);
    fitness += (chromosome.at(2)*ParametersSet::hitPointsCoeff);
    fitness += (chromosome.at(3)*ParametersSet::metabolismCoeff);
    fitness += (chromosome.at(4)*ParametersSet::foodCapacityCoeff);
    fitness += (chromosome.at(5)*ParametersSet::exhLevelCoeff);

    return fitness;
}

template <typename T>
QVector<size_t> sort_indexes(const QVector<T> &v) {

  // initialize original index locations
  QVector<size_t> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

  return idx;
}


template <class T1, class T2, class Pred = std::greater<T2> >
struct sort_pair_second {
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(left.second, right.second);
    }
};

void EvolutionaryAlg::selectMiBest(int mi, QVector<Animal *> &PopParentChild)
{
    QVector<std::pair<Animal*, double>> indivFitness;
    QVector<Animal *> newPop;

    for (auto &indiv: PopParentChild )
    {
        indivFitness.push_back(std::make_pair(indiv, this->fitnessFunction(indiv->featuresToChromosome())));
    }

    std::sort(indivFitness.begin(), indivFitness.end(), sort_pair_second<Animal*, double>());

    // w 17 mozna na kolekcji
    std::transform(indivFitness.begin(),
                   indivFitness.end(),
                   std::back_inserter(newPop),
                   [](const std::pair<Animal*, double>& indivFitness) { return indivFitness.first; }); //  mozna const auto w c++17

    // select best mi individuals from the population of size mi+lambda
    newPop.resize(mi);
    PopParentChild = newPop;

}

void EvolutionaryAlg::selectRoulette(int mi, QVector<Animal *> &PopParentChild)
{


}

void EvolutionaryAlg::selectRank(int mi, QVector<Animal *> &PopParentChild)
{

}

struct rangegenerator {
    rangegenerator(int init) : start(init) { }

    int operator()() {
        return start++;
    }

    int start;
};

class Generator {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    double min;
    double max;
    double mean;
    double stddev;
public:
    Generator(double mean, double stddev, double min, double max):
        distribution(mean, stddev), min(min), max(max), mean(mean), stddev(stddev)
    {}

    double operator ()() {
        while (true) {
            double number = this->distribution(generator);
            if (number >= this->min && number <= this->max)
                return number;
        }
    }

    double getMean() const
    {
        return mean;
    }

    double getStddev() const
    {
        return stddev;
    }

    double getMin() const
    {
        return min;
    }

    double getMax() const
    {
        return max;
    }
};


double EvolutionaryAlg::randomDouble(double min, double max)
{
    return min + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(max - min)));
}


// new individual will be added to Initial population
void EvolutionaryAlg::initializeIndividualVectors(int X, int Y, Beings beingType, QVector<Animal *> &IniPop)
{
    // possible solution: to tighten the boundaries for stddev
    // parameters: mean, sigma, min, max
    Generator genExh(ParametersSet::maxExhaustionLevel *0.3, (ParametersSet::maxExhaustionLevel-ParametersSet::minExhaustionLevel) * randomDouble(0.2, 0.3), ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
    Generator genHitPts(ParametersSet::maxHitPoints *0.7, (ParametersSet::maxHitPoints - ParametersSet::minHitPoints) * randomDouble(0.2, 0.8), ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * randomDouble(0.1, 0.2), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);
    // do rzutowania static_cast

    //    Generator genAge((ParametersSet::maxAge - ParametersSet::minAge) *0.5,(ParametersSet::maxAge - ParametersSet::minAge) * randomDouble(0.2, 0.4), ParametersSet::minAge, ParametersSet::maxAge);

    QVector<double> stdDevs;
    QVector<int> features;
    stdDevs.push_back(genEye.getMean());

    Being* being;
//    Being* beingConstr; being containing features with constraints


    if (beingType == Beings::PREDATOR)
    {
        Generator genPredSpeed((ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * 0.5,(ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * randomDouble(0.4, 0.5), ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed);
        Generator genPredFoodCap((ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * 0.5,(ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * randomDouble(0.1, 0.2), ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity);
        Generator genPredMetabolism((ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * 0.5,(ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * randomDouble(0.1, 0.3), ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism);

        stdDevs.push_back(genPredSpeed.getStddev());
        stdDevs.push_back(genHitPts.getStddev());
        stdDevs.push_back(genPredMetabolism.getStddev());
        stdDevs.push_back(genPredFoodCap.getStddev());
        stdDevs.push_back(genExh.getStddev());

        features.push_back(static_cast<int>(round(genEye())));
        features.push_back(static_cast<int>(round(genPredSpeed())));
        features.push_back(static_cast<int>(round(genHitPts())));
        features.push_back(static_cast<int>(round(genPredMetabolism())));
        features.push_back(static_cast<int>(round(genPredFoodCap())));
        features.push_back(static_cast<int>(round(genExh())));

//        ConstrainedEyeSight eye = (int)round(genEye());
////        featuresConstrained.push_back(eye);

        being = static_cast<Being*>(new Predator(X, Y, features, stdDevs));

    }
    else if (beingType == Beings::HERBIVOROUS)
    {
        Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.5,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * randomDouble(0.4, 0.5), ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
        Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.5,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * randomDouble(0.1, 0.2), ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
        Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.5,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * randomDouble(0.1, 0.3), ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);
//        Generator genHerbSaturation((ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * 0.5,(ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSaturationRate, ParametersSet::maxHerbivorousSaturationRate);

        stdDevs.push_back(genHerbSpeed.getStddev());
        stdDevs.push_back(genHitPts.getStddev());
        stdDevs.push_back(genHerbMetabolism.getStddev());
        stdDevs.push_back(genHerbFoodCap.getStddev());
        stdDevs.push_back(genExh.getStddev());

        features.push_back(static_cast<int>(round(genEye())));
        features.push_back(static_cast<int>(round(genHerbSpeed())));
        features.push_back(static_cast<int>(round(genHitPts())));
        features.push_back(static_cast<int>(round(genHerbMetabolism())));
        features.push_back(static_cast<int>(round(genHerbFoodCap())));
        features.push_back(static_cast<int>(round(genExh())));

        // nie ma static_cast
        // smart_ptr dodać

        //dodac struct Eye {Eye(int, val); int value; double stddev;}

        // const auto eye = Eye().;

        // cechy we wspolnym namespace, np Feature::Eye
        // new Herbivorous(X, Y, Eye(genEye(), eyeGen.stdDev()), Speed())
        being = static_cast<Being*>(new Herbivorous(X, Y, features, stdDevs));
    }
    else
    {
        qDebug() << "WRONG BEING TYPE PASSED AS VALUE! ";
    }

    IniPop.push_back(qobject_cast<Animal*>(being));
}


// new individual will be added to Initial population
void EvolutionaryAlg::initializeIndividual(int X, int Y, Beings beingType, QVector<Animal *> &IniPop)
{
    // possible solution: to tighten the boundaries for stddev
    Generator genExh(ParametersSet::maxExhaustionLevel *0.5, (ParametersSet::maxExhaustionLevel-ParametersSet::minExhaustionLevel) * randomDouble(0.2, 0.8), ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
    Generator genHitPts(ParametersSet::maxHitPoints *0.7, (ParametersSet::maxHitPoints - ParametersSet::minHitPoints) * randomDouble(0.2, 0.8), ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * randomDouble(0.3, 0.4), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);

    //    Generator genAge((ParametersSet::maxAge - ParametersSet::minAge) *0.5,(ParametersSet::maxAge - ParametersSet::minAge) * randomDouble(0.2, 0.4), ParametersSet::minAge, ParametersSet::maxAge);

    QVector<double> stdDevs;
    stdDevs.push_back(genEye.getMean()); //


    // WIZYTATOR
    Being* being;
    if (beingType == Beings::PREDATOR)
    {
        Generator genPredSpeed((ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * 0.5,(ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * randomDouble(0.3, 0.4), ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed);
        Generator genPredFoodCap((ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * 0.5,(ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity);
        Generator genPredMetabolism((ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * 0.5,(ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism);

        stdDevs.push_back(genPredSpeed.getStddev());
        stdDevs.push_back(genHitPts.getStddev());
        stdDevs.push_back(genPredMetabolism.getStddev());
        stdDevs.push_back(genPredFoodCap.getStddev());
        stdDevs.push_back(genExh.getStddev());

          being = static_cast<Being*>(new Predator(X, Y, static_cast<int>(round(genEye())), static_cast<int>(round(genPredSpeed())), (int)round(genHitPts()),static_cast<int>(round(genPredMetabolism())),  static_cast<int>(round(genPredFoodCap())), static_cast<int>(round(genExh())), stdDevs));

    }
    else if (beingType == Beings::HERBIVOROUS)
    {
        Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.5,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
        Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.5,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
        Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.5,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);

        stdDevs.push_back(genHerbSpeed.getStddev());
        stdDevs.push_back(genHitPts.getStddev());
        stdDevs.push_back(genHerbMetabolism.getStddev());
        stdDevs.push_back(genHerbFoodCap.getStddev());
        stdDevs.push_back(genExh.getStddev());

        being = static_cast<Being*>(new Herbivorous(X, Y, static_cast<int>(round(genEye())), static_cast<int>(round(genHerbSpeed())), static_cast<int>(round(genHitPts())), static_cast<int>(round(genHerbMetabolism())),  static_cast<int>(round(genHerbFoodCap())), static_cast<int>(round(genExh())), stdDevs));

    }
    else
    {
        qDebug() << "WRONG BEING TYPE PASSED AS VALUE! ";
    }

    IniPop.push_back(qobject_cast<Animal*>(being));
}


void EvolutionaryAlg::initializePopulations(int N, QVector<Animal*>& predatorIniPop, QVector<Animal*>& herbivorousIniPop)
{

    // TODO: set mu as input parameter passed from UI
    // mu - size of the population
    int mu = 50;

    // TODO: resolve correct logical positions: X, Y
    QVector<int> indicesX(N*N);
    QVector<int> indicesY(N*N);

    generate(begin(indicesX), end(indicesX), rangegenerator(0));
    generate(begin(indicesY), end(indicesY), rangegenerator(0));

    random_shuffle(begin(indicesX), end(indicesX));
    random_shuffle(begin(indicesY), end(indicesY));

    for (int i=0; i< mu; ++i)
    {
//        qDebug() << indicesX[i] << " " << indicesY[i] ;

        initializeIndividualVectors(indicesX[i], indicesY[i], Beings::PREDATOR, predatorIniPop);
        initializeIndividualVectors(indicesX[i+2], indicesY[i+2], Beings::HERBIVOROUS, herbivorousIniPop);

    }

//    qDebug() << "Initialized predator pop size = " << predatorIniPop.size();
//    qDebug() << "Initialized herbivorous pop size = " << herbivorousIniPop.size();


}

QVector<Animal*> EvolutionaryAlg::generateTemporaryPopulation(int lambda, QVector<Animal*>& currentPop)
{
    QVector<Animal*> tmp;
    for (int i=0; i< lambda; ++i)
    {
        int index = (rand() % (int)(currentPop.size()));
        tmp.push_back(currentPop.at(index));
    }

    return tmp;
}

// zwracac przez wartosc
// auto x=fun()

// wzorzec strategii dla TYPE
void EvolutionaryAlg::reproducePopulation(QVector<Animal*>& tempPop, int type) // type: mean, interpolation
{
    QVector<Animal*> germs; // for each pair of tempPop <x_dash, sigma_dash>
    QVector<double> stdDevsChild1, stdDevsChild2;
    QVector<int> featuresChild1, featuresChild2;

    qDebug() << "TEMP POP SIZE = " << tempPop.size();
    Being* beingChild1;
    Being* beingChild2;

    for (int i=0; i< tempPop.size(); i+=2)
    {
        featuresChild1.clear();
        featuresChild2.clear();
        stdDevsChild1.clear();
        stdDevsChild2.clear();

        if(type ==1)
        {
            int j=0;
            for (auto &indiv : (tempPop.at(i)->getFeaturesEA())) // access by reference to avoid copying
            {
                double FeatureChild1 = 0.0;
                double FeatureChild2 = 0.0;
                FeatureChild1 += (indiv*0.25); // CHILD FEATURE
                FeatureChild2 += (indiv*0.75);
                FeatureChild1 += (0.75*tempPop.at(i+1)->getFeaturesEA().at(j));
                FeatureChild2 += (0.25*tempPop.at(i+1)->getFeaturesEA().at(j));
                j++;
                featuresChild1.push_back((int)(FeatureChild1));
                featuresChild2.push_back((int)(FeatureChild2));

            }

            j = 0;
            for (auto &stdDev : tempPop.at(i)->getStdDevs())
            {
                double StdChild1 = 0.0, StdChild2 = 0.0;
                StdChild1 += (0.25 * stdDev);
                StdChild1 += (0.75 * tempPop.at(i+1)->getStdDevs().at(j));
                StdChild2 += (0.75 * stdDev);
                StdChild2 += (0.25 * tempPop.at(i+1)->getStdDevs().at(j));
                j++;
                stdDevsChild1.push_back(StdChild1);
                stdDevsChild2.push_back(StdChild2);
            }
        }
        else if(type==2)
        {
            std::default_random_engine generator;
            std::normal_distribution<double> distribution(0.0, 1.0);
            double a = distribution(generator);

            int j=0;
            // for each of the features
            for (auto &indiv : tempPop.at(i)->getFeaturesEA()) // access by reference to avoid copying
            {
                double FeatureChild1 = 0.0;
                double FeatureChild2 = 0.0;
                FeatureChild1 = indiv*a;
                FeatureChild2 = indiv * (1-a);
                FeatureChild1 += ((1-a)*((tempPop.at(i+1)->getFeaturesEA()).at(j)));
                FeatureChild2 += (a*((tempPop.at(i+1)->getFeaturesEA()).at(j)));
                j++;
                featuresChild1.push_back(FeatureChild1);
                featuresChild2.push_back(FeatureChild2);
            }

            j = 0;
            for (auto &stdDev : tempPop.at(i)->getStdDevs())
            {
                double StdChild1 = 0.0, StdChild2 = 0.0;
                StdChild1 = a*stdDev;
                StdChild2 = (1-a)*stdDev;
                StdChild1 += ((1-a)*((tempPop.at(i+1)->getStdDevs()).at(j)));
                StdChild2 += (a*((tempPop.at(i+1)->getStdDevs()).at(j)));
                j++;
                stdDevsChild1.push_back(StdChild1);
                stdDevsChild2.push_back(StdChild2);

            }
        }
        else
        {
            qDebug() << "Wrong type provided!";
        }
       // TODO: Discuss what to do with X and Y
        if (tempPop.at(0)->type() == Beings::PREDATOR)
        {
            // TODO: change the position of being
        beingChild1 = static_cast<Being*>(new Predator(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), featuresChild1, stdDevsChild1));
        beingChild2 = static_cast<Being*>(new Predator(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), featuresChild2, stdDevsChild2));

        }
        else if (tempPop.at(0)->type() == Beings::HERBIVOROUS)
        {
            beingChild1 = static_cast<Being*>(new Herbivorous(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), featuresChild1, stdDevsChild1));
            beingChild2 = static_cast<Being*>(new Herbivorous(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), featuresChild2, stdDevsChild2));
        }
        else
        {
            qDebug() << "Wrong type provided! ";
        }
        germs.push_back(qobject_cast<Animal*>(beingChild1));
        germs.push_back(qobject_cast<Animal*>(beingChild2));
    }

    tempPop = germs;

}

void EvolutionaryAlg::printPopulation(QVector<Animal *> &Pop)
{
    // displaying population features and stdDevs
    for (const Animal* anim : Pop)
    {
        anim->displayFeatures();
        anim->displayStd();
    }
}

void EvolutionaryAlg::mutation(QVector<Animal *> &RepPop)
{
   //  stdDevs are generated using normal distribution
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    int n = RepPop.at(0)->getFeaturesEA().size();
    double tauPrim = 1/(sqrt(2*(double)n));
    double tau = 1/(sqrt(2*sqrt((double)n)));

    qDebug() << "Number of features = " << n;

    for (int i=0; i< RepPop.size(); ++i)
    {
        double psiIndiv = distribution(generator);
        QVector<double> newStdDevs;
        QVector<int> newFeatures;
        for (int j=0; j<(RepPop.at(i)->getStdDevs()).size(); ++j)
        {
            double psiFeatureStd = distribution(generator);
            double niFeature = distribution(generator);
            newStdDevs.push_back((RepPop.at(i)->getStdDevs()).at(j) * exp(tauPrim*psiIndiv + tau* psiFeatureStd));
            newFeatures.push_back(RepPop.at(i)->getFeaturesEA().at(j)+newStdDevs.at(j)*niFeature);
        }
        RepPop.at(i)->setStdDevs(newStdDevs);
        RepPop.at(i)->setFeaturesForEA(newFeatures);
    }
}

// whole Evolutionary Algorithm
void EvolutionaryAlg::runEA(int mi, int lambda, int iterations, int reproduceType, QVector<Animal*> &predPopulation, QVector<Animal*> &herbPopulation)
{
    QVector<Animal*> predatorIniPop = predPopulation;
    QVector<Animal*> herbivorousIniPop = herbPopulation;
    ParametersSet* set = ParametersSet::getInstance();

    QVector<Animal*> predatorTempPop;
    QVector<Animal*> herbivorousTempPop;
    QVector<Animal*> predParentsChildrenPop = predatorIniPop;
    QVector<Animal*> herbParentsChildrenPop = herbivorousIniPop;
    for (int i=0; i<iterations; ++i)
    {

//    qDebug() << "parent size = " << predParentsChildrenPop.size();
//    qDebug() << "Predator Temp pop generation..." ;
    predatorTempPop = this->generateTemporaryPopulation(lambda, predParentsChildrenPop);
//    qDebug() << "Herbivorous Temp pop generation..." ;
    herbivorousTempPop = this->generateTemporaryPopulation(lambda, herbParentsChildrenPop);
//    qDebug() << "temp size = " << predatorTempPop.size();
    this->reproducePopulation(predatorTempPop, reproduceType);
//    qDebug() << "temp size after reproduce = " << predatorTempPop.size();
    this->mutation(predatorTempPop);

//    qDebug() << "temp size after mutation = " << predatorTempPop.size();

    this->reproducePopulation(herbivorousTempPop, reproduceType);
    this->mutation(herbivorousTempPop);

//    predParentsChildrenPop.clear();
//    herbParentsChildrenPop.clear();
    predParentsChildrenPop = predParentsChildrenPop + predatorTempPop;
    herbParentsChildrenPop = herbParentsChildrenPop +  herbivorousTempPop;

//    qDebug() << "par+child  = " << predParentsChildrenPop.size();

    predatorTempPop.clear();
    herbivorousTempPop.clear();

    this->selectMiBest(mi, predParentsChildrenPop);
    this->selectMiBest(mi, herbParentsChildrenPop);

//    qDebug() << "mi selection  = " << predParentsChildrenPop.size();

    }
    predPopulation = predParentsChildrenPop;
    herbPopulation = herbParentsChildrenPop;

}


void EvolutionaryAlg::setMi(int value)
{
    mi_ = value;
}

int EvolutionaryAlg::getMi() const
{
    return mi_;
}

void EvolutionaryAlg::setLambda(int value)
{
    lambda_ = value;
}

int EvolutionaryAlg::getLambda() const
{
    return lambda_;
}

void EvolutionaryAlg::setMaxIters(int value)
{
    maxIters_ = value;
}

int EvolutionaryAlg::getMaxIters() const
{
    return maxIters_;
}

void EvolutionaryAlg::setReproductionType(int value)
{
    reproductionType_ = value;
}

int EvolutionaryAlg::getReproductionType() const
{
    return reproductionType_;
}

void EvolutionaryAlg::setSelectionType(int value) // smart ptr na ten wzorzec
{
    selectionType_ = value;
}

int EvolutionaryAlg::getSelectionType() const
{
    return selectionType_;
}
