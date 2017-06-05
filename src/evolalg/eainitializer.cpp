#include "src/evolalg/eainitializer.h"
#include "src/sugarscape/animal.h"


void EaInitializer::initialize(Herbivorous& herb, int X, int Y)
{
    Generator genExh(ParametersSet::maxExhaustionLevel *0.3, (ParametersSet::maxExhaustionLevel-ParametersSet::minExhaustionLevel) * (herb.randomDouble(0.2, 0.3)), ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
    Generator genHitPts(ParametersSet::maxHitPoints *0.7, (ParametersSet::maxHitPoints - ParametersSet::minHitPoints) * (herb.randomDouble(0.2, 0.8)), ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * (herb.randomDouble(0.1, 0.2)), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);
    Generator genHerbSpeed((ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * 0.5,(ParametersSet::maxHerbivorousSpeed - ParametersSet::minHerbivorousSpeed) * (herb.randomDouble(0.4, 0.5)), ParametersSet::minHerbivorousSpeed, ParametersSet::maxHerbivorousSpeed);
    Generator genHerbFoodCap((ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * 0.5,(ParametersSet::maxHerbivorousFoodCapacity - ParametersSet::minHerbivorousFoodCapacity) * (herb.randomDouble(0.1, 0.2)), ParametersSet::minHerbivorousFoodCapacity, ParametersSet::maxHerbivorousFoodCapacity);
    Generator genHerbMetabolism((ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * 0.5,(ParametersSet::maxHerbivorousMetabolism - ParametersSet::minHerbivorousMetabolism) * (herb.randomDouble(0.1, 0.3)), ParametersSet::minHerbivorousMetabolism, ParametersSet::maxHerbivorousMetabolism);

    Herbivorous::FeatureStd Eye(static_cast<int>(round(genEye())), genEye.getMean());
    Herbivorous::FeatureStd Speed(static_cast<int>(round(genHerbSpeed())), genHerbSpeed.getStddev());
    Herbivorous::FeatureStd HitPoints(static_cast<int>(round(genHitPts())), genHitPts.getStddev());
    Herbivorous::FeatureStd Metabolism(static_cast<int>(round(genHerbMetabolism())), genHerbMetabolism.getStddev());
    Herbivorous::FeatureStd FoodCapacity(static_cast<int>(round(genHerbFoodCap())), genHerbFoodCap.getStddev());
    Herbivorous::FeatureStd Exhaustion(static_cast<int>(round(genExh())), genExh.getStddev());

    herb.setFeatureStdevs(Eye, Speed, HitPoints, Metabolism, FoodCapacity, Exhaustion);
    herb.setLogX(X);
    herb.setLogY(Y);

}



void EaInitializer::initialize(Predator& pred, int X, int Y)
{
    Generator genExh(ParametersSet::maxExhaustionLevel *0.3, (ParametersSet::maxExhaustionLevel-ParametersSet::minExhaustionLevel) * (pred.randomDouble(0.2, 0.3)), ParametersSet::minExhaustionLevel, ParametersSet::maxExhaustionLevel);
    Generator genHitPts(ParametersSet::maxHitPoints *0.7, (ParametersSet::maxHitPoints - ParametersSet::minHitPoints) * (pred.randomDouble(0.2, 0.8)), ParametersSet::minHitPoints, ParametersSet::maxHitPoints);
    Generator genEye((ParametersSet::maxEyeSight - ParametersSet::minEyeSight) *0.5,(ParametersSet::maxEyeSight - ParametersSet::minEyeSight) * (pred.randomDouble(0.1, 0.2)), ParametersSet::minEyeSight, ParametersSet::maxEyeSight);
    Generator genPredSpeed((ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * 0.5,(ParametersSet::maxPredatorSpeed - ParametersSet::minPredatorSpeed) * (pred.randomDouble(0.4, 0.5)), ParametersSet::minPredatorSpeed, ParametersSet::maxPredatorSpeed);
    Generator genPredFoodCap((ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * 0.5,(ParametersSet::maxPredatorFoodCapacity - ParametersSet::minPredatorFoodCapacity) * (pred.randomDouble(0.1, 0.2)), ParametersSet::minPredatorFoodCapacity, ParametersSet::maxPredatorFoodCapacity);
    Generator genPredMetabolism((ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * 0.5,(ParametersSet::maxPredatorMetabolism - ParametersSet::minPredatorMetabolism) * (pred.randomDouble(0.1, 0.3)), ParametersSet::minPredatorMetabolism, ParametersSet::maxPredatorMetabolism);
    Predator::FeatureStd Eye(static_cast<int>(round(genEye())), genEye.getMean());
    Predator::FeatureStd Speed(static_cast<int>(round(genPredSpeed())), genPredSpeed.getStddev());
    Predator::FeatureStd HitPoints(static_cast<int>(round(genHitPts())), genHitPts.getStddev());
    Predator::FeatureStd Metabolism(static_cast<int>(round(genPredMetabolism())), genPredMetabolism.getStddev());
    Predator::FeatureStd FoodCapacity(static_cast<int>(round(genPredFoodCap())), genPredFoodCap.getStddev());
    Predator::FeatureStd Exhaustion(static_cast<int>(round(genExh())), genExh.getStddev());

    pred.setFeatureStdevs(Eye, Speed, HitPoints, Metabolism, FoodCapacity, Exhaustion);
//    pred.setFeaturesForEA(features);
//    pred.setStdDevs(stdDevs);
    pred.setLogX(X);
    pred.setLogY(Y);

}
