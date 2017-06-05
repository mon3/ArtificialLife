#include "src/evolalg/generator.h"

double Generator::operator ()() {
    while (true) {
        double number = this->distribution(generator);
        if (number >= this->min && number <= this->max)
            return number;
    }
}

double Generator::getMean() const
{
    return mean;
}

double Generator::getStddev() const
{
    return stddev;
}

double Generator::getMin() const
{
    return min;
}

double Generator::getMax() const
{
    return max;
}
