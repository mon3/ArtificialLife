#include "src/evolalg/meanreproduction.h"
typedef std::pair<int, int> Point;


void MeanReproduction::reproducePopulation(QVector<std::shared_ptr<Animal>> &tempPop)
{
    QVector<std::shared_ptr<Animal>> germs; // for each pair of tempPop <x_dash, sigma_dash>
    QVector<double> stdDevsChild1, stdDevsChild2;
    QVector<int> featuresChild1, featuresChild2;

    for (int i=0; i< tempPop.size(); i+=2)
    {
        featuresChild1.clear();
        featuresChild2.clear();
        stdDevsChild1.clear();
        stdDevsChild2.clear();


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
//        const float param = 0.5f;
//        auto const parent1 = static_cast<Being*>(tempPop.at(i));
//        auto const parent2 = static_cast<Being*>(tempPop.at(i+1));

//        ParametersSet* set = ParametersSet::getInstance();
//        Point child1Point = set->beingsInterpolation(parent1, parent2, param);
//        Point child2Point = set->beingsInterpolation(parent1, parent2, param);

        germs.push_back(tempPop.at(i)->createBeing(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), featuresChild1, stdDevsChild1));
        germs.push_back(tempPop.at(i)->createBeing(tempPop.at(i)->getLogX(), tempPop.at(i)->getLogY(), featuresChild2, stdDevsChild2));
    }

    tempPop = germs;

}
