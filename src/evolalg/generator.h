#ifndef GENERATOR_H
#define GENERATOR_H
#include <stdio.h>
#include <random>

/*!
 * \brief The Generator class generating random doubles within certain range.
 * The range is important for the standard deviations of the features of an
 * individual from EA, as the feature values calculated using stdDevs cannot exceed
 * certain values and cannot be smaller than lower limit for a feature.
 */
class Generator {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    /*!
     * \brief min - lower limit of a random double that will be generated.
     */
    double min;
    /*!
     * \brief max - upper limit of a random double that will be generated.
     */
    double max;
    /*!
     * \brief mean - parameter of normal distribution.
     */
    double mean;
    /*!
     * \brief stddev - parameter of normal distribution.
     */
    double stddev;
public:
    /*!
     * \brief Generator Constructor.
     * \param mean - first parameter of a normal distribution used to generate double within certain range.
     * \param stddev - second parameter of a normal distribution used to generate double within certain range.
     * \param min - lower limit for a random double that will be generated.
     * \param max - upper limit for a random double that will be generated.
     */
    Generator(double mean, double stddev, double min, double max):
        distribution(mean, stddev), min(min), max(max), mean(mean), stddev(stddev)
    {}

    /*!
     * \brief operator () allowing to immediately retrieve random double from the generator.
     * \return
     */
    double operator ()();

    /*!
     * \brief getMean - mean of the normal distribution used to generate random double.
     * \return mean(1st parameter) of the normal distribution.
     */
    double getMean() const;
    /*!
     * \brief getStddev - standard deviation of the normal distribution used to generate random double.
     * \return stdDev(2nd parameter) of the normal distribution.
     */
    double getStddev() const;
    /*!
     * \brief getMin - lower limit of the generated random double.
     * \return minimum value of an allowed random double.
     */
    double getMin() const;
    /*!
     * \brief getMax - upper limit of the generated random double.
     * \return maximum value of an allowed random double.
     */
    double getMax() const;
};





#endif // GENERATOR_H
