#ifndef GENERATOR_H
#define GENERATOR_H
#include <stdio.h>
#include <random>


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

    double operator ()();

    double getMean() const;
    double getStddev() const;
    double getMin() const;
    double getMax() const;
};





#endif // GENERATOR_H
