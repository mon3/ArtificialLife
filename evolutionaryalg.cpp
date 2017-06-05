#include "evolutionaryalg.h"

#include <QVector>
#include <QDebug>
#include <being.h>
#include <random>
#include <predator.h>
#include <herbivorous.h>
#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <reproduction.h>

EvolutionaryAlg::EvolutionaryAlg()
{}

// parametry do algorytmu
double EvolutionaryAlg::fitnessFunction(QVector<int> chromosome)
{
    double fitness = 0.0;

    fitness += (chromosome.at(0)*ParametersSet::eyeSightCoeff);
    fitness += (chromosome.at(1)*ParametersSet::speedCoeff);
    fitness += (chromosome.at(2)*ParametersSet::hitPointsCoeff);
    fitness += (chromosome.at(3)*ParametersSet::metabolismCoeff);
    fitness += (chromosome.at(4)*ParametersSet::foodCapacityCoeff);
    fitness += (chromosome.at(5)*ParametersSet::exhLevelCoeff);

    return fitness;
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

//void EvolutionaryAlg::selectRoulette(int mi, QVector<Animal *> &PopParentChild)
//{


//}

//void EvolutionaryAlg::selectRank(int mi, QVector<Animal *> &PopParentChild)
//{

//}

struct rangegenerator {
    rangegenerator(int init) : start(init) { }

    int operator()() {
        return start++;
    }

    int start;
};

double EvolutionaryAlg::randomDouble(double min, double max)
{
    return min + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(max - min)));
}


void EvolutionaryAlg::initializePopulations(int N, QVector<Animal*>& predatorIniPop, QVector<Animal*>& herbivorousIniPop)
{
    EaInitializer eaInitializer;
    // TODO: set mu as input parameter passed from UI
    // mu - size of the population
    int mu = 50;

    // TODO: resolve correct logical positions: X, Y; check the correct way of initializing positions
    QVector<int> indicesX(N*N);
    QVector<int> indicesY(N*N);

    generate(begin(indicesX), end(indicesX), rangegenerator(0));
    generate(begin(indicesY), end(indicesY), rangegenerator(0));

    random_shuffle(begin(indicesX), end(indicesX));
    random_shuffle(begin(indicesY), end(indicesY));

    // initialization of individual vectors for Predator and Herbivorous POpulations
    for (int i=0; i< mu; ++i)
    {
        predatorIniPop.push_back(new Predator(indicesX[i], indicesY[i]));
        herbivorousIniPop.push_back(new Herbivorous(indicesX[i+2], indicesY[i]));
        predatorIniPop.at(i)->acceptInitializer(eaInitializer,indicesX[i], indicesY[i]);
        herbivorousIniPop.at(i)->acceptInitializer(eaInitializer, indicesX[i+2], indicesY[i+2]);
    }

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
void EvolutionaryAlg::reproducePopulation(QVector<Animal*>& tempPop, int type) // type: mean - 0 , interpolation -1
{
      Reproduction reproduction;
      reproduction.setStrategy(type);
      reproduction.reproduce(tempPop);
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

    QVector<Animal*> predParentsChildrenPop = predatorIniPop;
    QVector<Animal*> herbParentsChildrenPop = herbivorousIniPop;
    for (int i=0; i<iterations; ++i)
    {

    auto predatorTempPop = this->generateTemporaryPopulation(lambda, predParentsChildrenPop);
    auto herbivorousTempPop = this->generateTemporaryPopulation(lambda, herbParentsChildrenPop);
    this->reproducePopulation(predatorTempPop, reproduceType);
    this->mutation(predatorTempPop);


    this->reproducePopulation(herbivorousTempPop, reproduceType);
    this->mutation(herbivorousTempPop);

    predParentsChildrenPop = predParentsChildrenPop + predatorTempPop;
    herbParentsChildrenPop = herbParentsChildrenPop +  herbivorousTempPop;

    predatorTempPop.clear();
    herbivorousTempPop.clear();

    this->selectMiBest(mi, predParentsChildrenPop);
    this->selectMiBest(mi, herbParentsChildrenPop);
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
