#ifndef EVOLUTIONARYALG_H
#define EVOLUTIONARYALG_H

#include <QVector>
#include <src/sugarscape/animal.h>

#include "src/evolalg/eainitializer.h"

 class EvolutionaryAlg
 {
//  Q_OBJECT

 public:
    EvolutionaryAlg();
    EvolutionaryAlg(int mi, int lambda, int maxIters, int reproductionType, int selectionType): mi_(mi), lambda_(lambda),
        maxIters_(maxIters), reproductionType_(reproductionType), selectionType_(selectionType) {}

    void initializePopulations(int N, QVector<Animal*>& predatorIniPop, QVector<Animal*>& herbivorousIniPop);
    void initializeIndividual(int X, int Y, Beings beingType, QVector<Animal*>& IniPop);
    void initializeIndividualVectors(int X, int Y, Beings beingType, QVector<Animal *> &IniPop);
    void mutation(QVector<Animal *> &RepPop);
    void printPopulation(QVector<Animal *> &Pop);
    double fitnessFunction(QVector<int> chromosome);
    double normalizeFeature(int feature, int min, int max);
    void selectMiBest(int mi, QVector<Animal *> &PopParentChild); // will be reduced to next population of mi individuals
//    void selectRoulette(int mi, QVector<Animal *> &PopParentChild); // roulette rule selection
//    void selectRank(int mi, QVector<Animal *> &PopParentChild); // rank selection


    double randomDouble(double min, double max);
    // for std::vector compiler optimizes -> move is called if tmp is not used
    // TODO: check the conditions for QVector
    QVector<Animal*> generateTemporaryPopulation(int lambda, QVector<Animal*>& currentPop);
    void reproducePopulation(QVector<Animal*>& tempPop, int type); // type: mean - 0, interpolation - 1
    void runEA(int mi, int lambda, int iterations, int reproduceType, QVector<Animal*> &predPopulation, QVector<Animal*> &herbPopulation);

    //mi - population size, lambda - chil, n - number of alleles in chromosome
   //  Animal: herbivorous or predator
     EvolutionaryAlg(int mi, int lambda, int n, Animal* animal);

     void setMi(int value);
     int getMi() const;

     void setLambda(int value);
     int getLambda() const;

     void setMaxIters(int value);
     int getMaxIters() const;

     void setReproductionType(int value);
     int getReproductionType() const;

     void setSelectionType(int value);
     int getSelectionType() const;


 private:
     int mi_; // size of parent population
     int lambda_; // size of children population
     int maxIters_; // maximum number of iterations of EA
     int reproductionType_; // reproduction type: 1 - mean; 2 - interpolation
     int selectionType_; // selection type: 1 - mi best; 2 - roulette rule, 3 - tournament
};



#endif // EVOLUTIONARYALG_H
