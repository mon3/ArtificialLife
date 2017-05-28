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

QVector<int> EvolutionaryAlg::featuresToChromosome(Animal *animal)
{
    QVector<int> chromosome;
    int beingType = animal->type();
    chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[0], ParametersSet::minEyeSight, ParametersSet::maxEyeSight)); //common

    if (beingType == Beings::PREDATOR)
    {

        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[1], ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed));
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[2], ParametersSet::minHitPoints, ParametersSet::maxHitPoints)); //common
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[3], ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism));
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[4], ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity));
    }
    else if (beingType == Beings::HERBIVOROUS)
    {
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[1], ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed));
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[2], ParametersSet::minHitPoints, ParametersSet::maxHitPoints)); //common
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[3], ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism));
        chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[4], ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity));
    }

    chromosome.push_back(normalizeFeature(animal->getFeaturesEA()[5], ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel)); //common

    return chromosome;
}


double calculation(double a, double b, double c)
{
  double d = abs(100 * (a - b) /(c - b));
  return d;
}

double EvolutionaryAlg::normalizeFeature(int feature,int min, int max)
{
    double res = calculation(feature, min, max);
    return res;
}

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
        indivFitness.push_back(std::make_pair(indiv, this->fitnessFunction(this->featuresToChromosome(indiv))));
    }

    std::sort(indivFitness.begin(), indivFitness.end(), sort_pair_second<Animal*, double>());

//    for (unsigned i = 0; i< indivFitness.size(); ++i)
//    {
//        qDebug() << "FITNESS = " << indivFitness[i].second ;
//    }


    std::transform(indivFitness.begin(),
                   indivFitness.end(),
                   std::back_inserter(newPop),
                   [](const std::pair<Animal*, double>& indivFitness) { return indivFitness.first; });

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
    Generator genEye((double)((double)(ParametersSet::maxEyeSight) ) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * randomDouble(0.1, 0.2), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);

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

        features.push_back((int)round(genEye()));
        features.push_back((int)round(genPredSpeed()));
        features.push_back((int)round(genHitPts()));
        features.push_back((int)round(genPredMetabolism()));
        features.push_back((int)round(genPredFoodCap()));
        features.push_back((int)round(genExh()));

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

        features.push_back((int)round(genEye()));
        features.push_back((int)round(genHerbSpeed()));
        features.push_back((int)round(genHitPts()));
        features.push_back((int)round(genHerbMetabolism()));
        features.push_back((int)round(genHerbFoodCap()));
        features.push_back((int)round(genExh()));

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

          being = static_cast<Being*>(new Predator(X, Y, (int)round(genEye()), (int)round(genPredSpeed()), (int)round(genHitPts()), (int)round(genPredMetabolism()),  (int)round(genPredFoodCap()), (int)round(genExh()), stdDevs));

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

        being = static_cast<Being*>(new Herbivorous(X, Y, (int)round(genEye()), (int)round(genHerbSpeed()), (int)round(genHitPts()), (int)round(genHerbMetabolism()),  (int)round(genHerbFoodCap()), (int)round(genExh()), stdDevs));

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

void EvolutionaryAlg::reproducePopulation(QVector<Animal*>& tempPop, int type) // type: mean, interpolation
{
    QVector<Animal*> germs; // for each pair of tempPop <x_dash, sigma_dash>
    QVector<double> stdDevs, stdDevs2;
    QVector<int> features, features2;

    qDebug() << "TEMP POP SIZE = " << tempPop.size();
    Being* being;
    Being* being2;

    for (int i=0; i< tempPop.size(); i+=2)
    {
        features.clear();
        features2.clear();
        stdDevs.clear();
        stdDevs2.clear();

        if(type ==1)
        {
            int j=0;
            for (auto &indiv : (tempPop.at(i)->getFeaturesEA())) // access by reference to avoid copying
            {
                double newFeature = 0.0;
                double newFeature2 = 0.0;
                newFeature += (indiv*0.25);
                newFeature2 += (indiv*0.75);
                newFeature += (0.75*tempPop.at(i+1)->getFeaturesEA().at(j));
                newFeature2 += (0.25*tempPop.at(i+1)->getFeaturesEA().at(j));
                j++;
                features.push_back((int)(newFeature));
                features2.push_back((int)(newFeature2));

            }

            j = 0;
            for (auto &stdDev : tempPop.at(i)->getStdDevs())
            {
                double newStd = 0.0, newStd2 = 0.0;
                newStd += (0.25 * stdDev);
                newStd += (0.75 * tempPop.at(i+1)->getStdDevs().at(j));
                newStd2 += (0.75 * stdDev);
                newStd2 += (0.25 * tempPop.at(i+1)->getStdDevs().at(j));
                j++;
                stdDevs.push_back(newStd);
                stdDevs2.push_back(newStd2);
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
                double newFeature = 0.0;
                double newFeature2 = 0.0;
                newFeature = indiv*a;
                newFeature2 = indiv * (1-a);
                newFeature += ((1-a)*((tempPop.at(i+1)->getFeaturesEA()).at(j)));
                newFeature2 += (a*((tempPop.at(i+1)->getFeaturesEA()).at(j)));
                j++;
                features.push_back(newFeature);
                features2.push_back(newFeature2);
            }

            j = 0;
            for (auto &stdDev : tempPop.at(i)->getStdDevs())
            {
                double newStd = 0.0, newStd2 = 0.0;
                newStd = a*stdDev;
                newStd2 = (1-a)*stdDev;
                newStd += ((1-a)*((tempPop.at(i+1)->getStdDevs()).at(j)));
                newStd2 += (a*((tempPop.at(i+1)->getStdDevs()).at(j)));
                j++;
                stdDevs.push_back(newStd);
                stdDevs2.push_back(newStd2);

            }
        }
        else
        {
            qDebug() << "Wrong type provided!";
        }
       // TODO: Discuss what to do with X and Y
        if (tempPop.at(0)->type() == Beings::PREDATOR)
        {
        being = static_cast<Being*>(new Predator(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), features, stdDevs));
        being2 = static_cast<Being*>(new Predator(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), features2, stdDevs2));

        }
        else if (tempPop.at(0)->type() == Beings::HERBIVOROUS)
        {
            being = static_cast<Being*>(new Herbivorous(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), features, stdDevs));
            being2 = static_cast<Being*>(new Herbivorous(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), features2, stdDevs2));
        }
        else
        {
            qDebug() << "Wrong type provided! ";
        }
        germs.push_back(qobject_cast<Animal*>(being));
        germs.push_back(qobject_cast<Animal*>(being2));
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
        if(RepPop.at(0)->type() == Beings::PREDATOR)
        {
            RepPop.at(i)->setFeaturesEA(newFeatures, Beings::PREDATOR);
        }
        else if(RepPop.at(0)->type() == Beings::HERBIVOROUS)
        {
            RepPop.at(i)->setFeaturesEA(newFeatures, Beings::HERBIVOROUS);
        }
        else
        {
            qDebug() << "Wrong type provided! ";
        }
    }

//    printPopulation(RepPop);
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
