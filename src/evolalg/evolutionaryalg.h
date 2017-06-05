#ifndef EVOLUTIONARYALG_H
#define EVOLUTIONARYALG_H

#include <QVector>
#include <src/sugarscape/animal.h>

#include "src/evolalg/eainitializer.h"

/*!
  * \brief The EvolutionaryAlg class providing all methods allowing to run EA on a given Population.
  */

 class EvolutionaryAlg
 {

 public:
     /*!
     * \brief EvolutionaryAlg Constructor.
     */
    EvolutionaryAlg();

    /*!
      * \brief EvolutionaryAlg Constructor.
      * \param mi - size of the population in each iteration of EA.
      * \param lambda - size of the temporary population.
      * \param n - size of the grid in X/Y direction.
      */
     EvolutionaryAlg(int mi, int lambda, int n);

    /*!
     * \brief EvolutionaryAlg Constructor using parameters passed by user (in code or from gui).
     * \param mi - size of the population.
     * \param lambda - size of temporary population (of descendants).
     * \param maxIters - number of Evolutionary Algorithm iterations.
     * \param reproductionType - type of the reproduction: mean(0), interpolation(1).
     * \param selectionType - type of selection of individuals after reproduction to children
     * population (mi best selection implemented).
     */
    EvolutionaryAlg(int mi, int lambda, int maxIters, int reproductionType, int selectionType): mi_(mi), lambda_(lambda),
        maxIters_(maxIters), reproductionType_(reproductionType), selectionType_(selectionType) {}

    /*!
     * \brief initializePopulations - providing Herbivorous and Predator initial Populations initialization.
     * \param N - number of grid size in X/Y direction.
     * \param predatorIniPop - initial Predator population.
     * \param herbivorousIniPop - initial Herbivorous population.
     * \param mu - size of the Population.
     */
    void initializePopulations(int N, QVector<std::shared_ptr<Animal>>& predatorIniPop, QVector<std::shared_ptr<Animal>>& herbivorousIniPop, int mu);
    /*!
     * \brief mutation - providing mutation of the individuals of Temporary Population.
     * \param RepPop - Reproduce Population (after crossing-over).
     */
    void mutation(QVector<std::shared_ptr<Animal>> &RepPop);
    /*!
     * \brief printPopulation - displaying features and standard deviations for every individual in the population.
     * \param Pop - population, for which individuals features and stdDevs will be displayed.
     */
    void printPopulation(QVector<std::shared_ptr<Animal> > &Pop);
    /*!
     * \brief fitnessFunction - providing possibility to calculate fitness function for the individual.
     * \param chromosome - representing individual in a population.
     * \return the result of calculation of fitness function.
     */
    double fitnessFunction(QVector<int> chromosome);
    /*!
     * \brief selectMiBest - providing mi best selection approach.
     * \param mi - size of the population.
     * \param PopParentChild - temporary population of parents and children reduced to mi best child population.
     */
    void selectMiBest(int mi, QVector<std::shared_ptr<Animal>> &PopParentChild); // will be reduced to next population of mi individuals

    /*!
     * \brief generateTemporaryPopulation - temporary population generation from mi individuals lambda children (lambda>mi).
     * \param lambda - size of temporary population.
     * \param currentPop - source population of mi individuals.
     * \return generated temporary population.
     */
    QVector<std::shared_ptr<Animal>> generateTemporaryPopulation(int lambda, QVector<std::shared_ptr<Animal>>& currentPop);
    /*!
     * \brief reproducePopulation - method providing the reproduction process of temporary population, containing lambda individuals.
     *  Implemented using Strategy Pattern.
     * \param tempPop - temporary population that will be reproduced.
     * \param type - reproduction type: mean(0), interpolation(1). Depending on the type aprropriate reproduce function will be called.
     */
    void reproducePopulation(QVector<std::shared_ptr<Animal>>& tempPop, int type);
    /*!
     * \brief runEA - method allowing to process the whole Evolutionary Algorithm.
     * \param mi - size of the population in each iteration of Evolutionary Algorithm.
     * \param lambda - size of the temporary population (in crossing-over and mutation).
     * \param iterations - number of Evolutionary Algorithm iterations.
     * \param reproduceType - reproduction type: mean(0), interpolation(1).
     * \param predPopulation - population of class Predator that will be processed by EA.
     * \param herbPopulation - population of class Herbivorous that will be processed by EA.
     */
    void runEA(int mi, int lambda, int iterations, int reproduceType, QVector<std::shared_ptr<Animal>> &predPopulation, QVector<std::shared_ptr<Animal>> &herbPopulation);

    /*!
      * \brief setMi - setter of parameter mi - size of the population processed by EA.
      * \param value - population size.
      */
     void setMi(int value);
     /*!
      * \brief getMi - returns the size of the population processed by EA.
      * \return population size that is processed by EA.
      */
     int getMi() const;

     /*!
      * \brief setLambda - setter of parameter lambda - size of the temporary population processed by EA.
      * \param value - size of the temporary population.
      */
     void setLambda(int value);
     /*!
      * \brief getLambda - returns the size of the temporary population processed by EA.
      * \return temporary population size.
      */
     int getLambda() const;

     /*!
      * \brief setMaxIters - setter for number of Evolutionary Algorithm iterations.
      * \param value - number of EA iterations.
      */
     void setMaxIters(int value);
     int getMaxIters() const;

     /*!
      * \brief setReproductionType - setter for reproduction type: mean(0), interpolation(1).
      * \param value
      */
     void setReproductionType(int value);
     /*!
      * \brief getReproductionType - returns the type of reproduction used by EA: mean(0), interpolation(1).
      * \return reproduction type.
      */
     int getReproductionType() const;

     /*!
      * \brief setSelectionType - setter for a selection method: mi best(1) implemented.
      * \param value - selection type: mi best(1).
      */
     void setSelectionType(int value);
     /*!
      * \brief getSelectionType - returns the type of Selection method.
      * \return selection method: mi best(0) implemented.
      */
     int getSelectionType() const;


 private:
     /*!
      * \brief mi_ - size of the population processed by EA.
      */
     int mi_;
     /*!
      * \brief lambda_ - size of temporary population
      */
     int lambda_;
     /*!
      * \brief maxIters_ - maximum number of iterations of EA.
      */
     int maxIters_;
     /*!
      * \brief reproductionType_ - reproduction type: mean(0), interpolation(1).
      */
     int reproductionType_;
     /*!
      * \brief selectionType_ - selection type: mi best(1).
      */
     int selectionType_;
};



#endif // EVOLUTIONARYALG_H
