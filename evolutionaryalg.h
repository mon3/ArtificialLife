#ifndef EVOLUTIONARYALG_H
#define EVOLUTIONARYALG_H

#include <QVector>
#include <animal.h>

 class EvolutionaryAlg
 {
//  Q_OBJECT

 public:
    EvolutionaryAlg();
    QVector<int> featuresToChromosome(Animal* animal);
    void initializePopulations(int N, QVector<Animal*>& predatorIniPop, QVector<Animal*>& herbivorousIniPop);
    void initializeIndividual(int X, int Y, Beings beingType, QVector<Animal*>& IniPop);
    void initializeIndividualVectors(int X, int Y, Beings beingType, QVector<Animal *> &IniPop);
    void mutation(QVector<Animal *> &RepPop);
    void printPopulation(QVector<Animal *> &Pop);
    double fitnessFunction(QVector<int> chromosome);
    double normalizeFeature(int feature, int min, int max);
    void selectMiBest(int mi, QVector<Animal *> &PopParentChild); // will be reduced to next population of mi individuals
    void selectRoulette(int mi, QVector<Animal *> &PopParentChild); // roulette rule selection
    void selectRank(int mi, QVector<Animal *> &PopParentChild); // roulette rule selection


    double randomDouble(double min, double max);
    // for std::vector compiler optimizes -> move is called if tmp is not used
    // TODO: check the conditions for QVector
    QVector<Animal*> generateTemporaryPopulation(int lambda, QVector<Animal*>& currentPop);
    void reproducePopulation(QVector<Animal*>& tempPop, int type); // type: mean, interpolation


    //mi - population size, lambda - chil, n - number of alleles in chromosome
   //  Animal: herbivorous or predator
     EvolutionaryAlg(int mi, int lambda, int n, Animal* animal);

};



#endif // EVOLUTIONARYALG_H
