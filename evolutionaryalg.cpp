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
      qDebug() << "Konstruktor EA. " ;
}

QVector<int> EvolutionaryAlg::featuresToChromosome(Animal *animal)
{
    QVector<int> chromosome;
//    int beingType = animal->type();
//    if (beingType == Beings::PREDATOR)
//    {
//        qDebug() << "predator";
//    }
//    else if (beingType == Beings::HERBIVOROUS)
//        {
//            qDebug() << "herbivorous";
//        }
    chromosome.push_back(animal->getEyeSight());
    chromosome.push_back(animal->getSpeed());
    chromosome.push_back(animal->getHitPoints());
    chromosome.push_back(animal->getMetabolism());
    chromosome.push_back(animal->getFoodCapacity());
    chromosome.push_back(animal->getExhaustionLevel());
    return chromosome;
}


//int random(int min, int max) //range : [min, max)
//{
//   static bool first = true;
//   if ( first )
//   {
//      srand(time(NULL)); //seeding for the first time only!
//      first = false;
//   }
//   return min + rand() % (max - min);
//}


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
    Generator genExh(ParametersSet::maxExhaustionLevel *0.5, (ParametersSet::maxExhaustionLevel-ParametersSet::minExhaustionLevel) * randomDouble(0.2, 0.8), ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
    Generator genHitPts(ParametersSet::maxHitPoints *0.7, (ParametersSet::maxHitPoints - ParametersSet::minHitPoints) * randomDouble(0.2, 0.8), ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * randomDouble(0.3, 0.4), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);

    //    Generator genAge((ParametersSet::maxAge - ParametersSet::minAge) *0.5,(ParametersSet::maxAge - ParametersSet::minAge) * randomDouble(0.2, 0.4), ParametersSet::minAge, ParametersSet::maxAge);

    QVector<double> stdDevs;
    QVector<int> features;
    stdDevs.push_back(genEye.getMean());





//    QVector<ConstrainedValue> featuresConstrained;
//    QVector<ConstrainedValue> stdDevsBound;



    Being* being;
//    Being* beingConstr; being containing features with constraints


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

        features.push_back((int)round(genEye()));
        features.push_back((int)round(genPredSpeed()));
        features.push_back((int)round(genHitPts()));
        features.push_back((int)round(genPredMetabolism()));
        features.push_back((int)round(genPredFoodCap()));
        features.push_back((int)round(genExh()));

        ConstrainedEyeSight eye = (int)round(genEye());
//        featuresConstrained.push_back(eye);



        being = static_cast<Being*>(new Predator(X, Y, features, stdDevs));

    }
    else if (beingType == Beings::HERBIVOROUS)
    {
        Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.5,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
        Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.5,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
        Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.5,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);
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
//    stdDevs.push_back(genHitPts.getStddev());
    stdDevs.push_back(genEye.getMean());
//    stdDevs.push_back(genAge.getMean());

//    qDebug() << "SIGMA: ";
//    qDebug() << "hitpts = " << genHitPts.getStddev();
//    qDebug() << "Eye = " << genEye.getStddev();
//    qDebug() << "Age = " << genAge.getStddev();


    Being* being;


    if (beingType == Beings::PREDATOR)
    {
        Generator genPredSpeed((ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * 0.5,(ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * randomDouble(0.3, 0.4), ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed);
        Generator genPredFoodCap((ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * 0.5,(ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity);
        Generator genPredMetabolism((ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * 0.5,(ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism);
//        Generator genPredSaturation((ParametersSet::maxPredatorSaturationRate - ParametersSet::minPredatorSaturationRate) * 0.5,(ParametersSet::maxPredatorSaturationRate - ParametersSet::minPredatorSaturationRate) * randomDouble(0.2, 0.4), ParametersSet::minPredatorSaturationRate, ParametersSet::maxPredatorSaturationRate);


        stdDevs.push_back(genPredSpeed.getStddev());
        stdDevs.push_back(genHitPts.getStddev());
        stdDevs.push_back(genPredMetabolism.getStddev());
        stdDevs.push_back(genPredFoodCap.getStddev());
        stdDevs.push_back(genExh.getStddev());
//        stdDevs.push_back(genPredSaturation.getStddev());

//        qDebug() << "speed = " << genPredSpeed.getStddev();
//        qDebug() << "foodcap = " << genPredFoodCap.getStddev();
//        qDebug() << "metabolism = " << genPredMetabolism.getStddev();
//        qDebug() << "Exh = " << genExh.getStddev();
//        qDebug() << "saturation = " << genPredSaturation.getStddev();

//        qDebug() << "GEN hitpts = " << genHitPts();
//        qDebug() << "GEN Eye = " << genEye();
//        qDebug() << "GEN Age = " << genAge();



//        being = static_cast<Being*>(new Predator(X, Y,(int)round(genHitPts()), (int)round(genEye()), (int)round(genAge()), 1, (int)round(genPredSpeed()), (int)round(genPredFoodCap()), (int)round(genPredMetabolism()), (int)round(genExh()), (int)round(genPredSaturation()), stdDevs));
          being = static_cast<Being*>(new Predator(X, Y, (int)round(genEye()), (int)round(genPredSpeed()), (int)round(genHitPts()), (int)round(genPredMetabolism()),  (int)round(genPredFoodCap()), (int)round(genExh()), stdDevs));

    }
    else if (beingType == Beings::HERBIVOROUS)
    {
        Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.5,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
        Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.5,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
        Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.5,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);
//        Generator genHerbSaturation((ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * 0.5,(ParametersSet::maxHerbivorousSaturationRate - ParametersSet::minHerbivorousSaturationRate) * randomDouble(0.2, 0.4), ParametersSet::minHerbivorousSaturationRate, ParametersSet::maxHerbivorousSaturationRate);

        stdDevs.push_back(genHerbSpeed.getStddev());
        stdDevs.push_back(genHitPts.getStddev());
        stdDevs.push_back(genHerbMetabolism.getStddev());
        stdDevs.push_back(genHerbFoodCap.getStddev());
        stdDevs.push_back(genExh.getStddev());

/*      qDebug() << "speed = " << genHerbSpeed.getStddev();
        qDebug() << "foodcap = " << genHerbFoodCap.getStddev();
        qDebug() << "metabolism = " << genHerbMetabolism.getStddev();
        qDebug() << "Exh = " << genExh.getStddev();
        qDebug() << "saturation = " << genHerbSaturation.getStddev(); */

//        being = static_cast<Being*>(new Herbivorous(X, Y, (int)round(genHitPts()), (int)round(genEye()), (int)round(genAge()), 1, (int)round(genHerbSpeed()), (int)round(genHerbFoodCap()), (int)round(genHerbMetabolism()), (int)round(genExh()), (int)round(genHerbSaturation()), stdDevs));
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

    // mu - size of the population
//    int mu = int(N * N * 0.2);
    int mu = 20;
    qDebug() << "Initial pop size: " << mu << endl;

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

    qDebug() << "Initialized predator pop size = " << predatorIniPop.size();
    qDebug() << "Initialized herbivorous pop size = " << herbivorousIniPop.size();


}

QVector<Animal*> EvolutionaryAlg::generateTemporaryPopulation(int lambda, QVector<Animal*>& currentPop)
{
    QVector<Animal*> tmp;
    for (int i=0; i< lambda; ++i)
    {

        int index = (rand() % (int)(currentPop.size()));
//        qDebug() << "INDEXES: ";
//        qDebug() << index ;

        tmp.push_back(currentPop.at(index));
    }

//            qDebug() << '\n';


    return tmp;
}

void EvolutionaryAlg::reproducePopulation(QVector<Animal*>& tempPop, int type) // type: mean, interpolation
{
    QVector<Animal*> germs; // for each pair of tempPop <x_dash, sigma_dash>
    QVector<double> stdDevs;
    QVector<int> features;

    qDebug() << "TEMP POP SIZE = " << tempPop.size();
    Being* being;

    for (int i=0; i< tempPop.size(); i+=2)
    {
        features.clear();
        stdDevs.clear();
//        qDebug() <<"INDEKSY = " << i;

        // for std
//        std::transform(tempPop.at(i)->getFeaturesEA().begin(), tempPop.at(i)->getFeaturesEA().end(), tempPop.at(i+1)->getFeaturesEA().begin(),tempPop.at(i)->getFeaturesEA().begin(), std::plus<int>());

        if(type ==1)
        {
            int j=0;
            for (auto &indiv : (tempPop.at(i)->getFeaturesEA())) // access by reference to avoid copying
            {
                int newFeature;
//                qDebug()<< "indiv type = " << j;
                newFeature += indiv;
                newFeature += tempPop.at(i+1)->getFeaturesEA().at(j);
                newFeature = newFeature/2;
                j++;
                qDebug() << "indiv to tempPop: " << newFeature;
                features.push_back(newFeature);
            }

            j = 0;
            for (auto &stdDev : tempPop.at(i)->getStdDevs())
            {
                stdDev += tempPop.at(i+1)->getStdDevs().at(j);
                stdDev = stdDev/2;
                j++;
                stdDevs.push_back(stdDev);
            }
        }
        else if(type==2)
        {
            std::default_random_engine generator;
            std::normal_distribution<double> distribution(0.0, 1.0);
            double a = distribution(generator);

            int j=0;
            for (auto &indiv : tempPop.at(i)->getFeaturesEA()) // access by reference to avoid copying
            {
//                qDebug()<< "j = " << j;
//                int newFeature;

//                newFeature += (a*indiv);
                indiv = indiv * a;
                indiv += ((1-a)*((tempPop.at(i+1)->getFeaturesEA()).at(j)));
                j++;
//                qDebug() << "INDIV = " << indiv;
                features.push_back(indiv);
            }

            j = 0;
            for (auto &stdDev : tempPop.at(i)->getStdDevs())
            {
//                double newStdDev;
                stdDev += (a*stdDev);
                //stdDev = stdDev * a;
                stdDev += ((1-a)*((tempPop.at(i+1)->getStdDevs()).at(j)));
                j++;
//                qDebug() << "SIGMA = " << stdDev;
                stdDevs.push_back(stdDev);
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
        }
        else if (tempPop.at(0)->type() == Beings::HERBIVOROUS)
        {
            being = static_cast<Being*>(new Herbivorous(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), features, stdDevs));
        }
        else
        {
            qDebug() << "Wrong type provided! ";
        }
        germs.push_back(qobject_cast<Animal*>(being));
    }

    tempPop = germs;
//    qDebug() << "TEMP po przepisaniu = " << tempPop.size();

}

void EvolutionaryAlg::printPopulation(QVector<Animal *> &RepPop)
{
    // wypisywanie populacji
    for (const Animal* anim : RepPop)
    {
        anim->displayFeatures();
        anim->displayStd();

    }

}

void EvolutionaryAlg::mutation(QVector<Animal *> &RepPop)
{
   //  stdDevs are ge.nerated using random distribution
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);

    int n = RepPop.at(0)->getFeaturesEA().size();
    double tauPrim = 1/(sqrt(2*n));
    double tau = 1/(sqrt(2*sqrt(n)));

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

    printPopulation(RepPop);
}
