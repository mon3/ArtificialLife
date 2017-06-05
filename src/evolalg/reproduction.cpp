#include "src/evolalg/reproduction.h"

Reproduction::Reproduction()
{
    strategy_ = NULL;
 }


void Reproduction::setStrategy(int type)
{
  delete strategy_;
  if (type == Mean)
    strategy_ = new MeanReproduction();
  else if (type == Interpolation)
    strategy_ = new InterpolationReproduction();
}

void Reproduction::reproduce(QVector<Animal*>& tempPop)
{
  strategy_->reproducePopulation(tempPop);
}
