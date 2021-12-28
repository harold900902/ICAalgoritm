#pragma once

#include <vector>
#include <cmath>
//#include <boost/math/constants/constants.hpp>


//This class contains the fitness function

class FitnessFunction
{

public:
     int dimension = 20;
private:
    double minVal = -2.048;
    double maxVal = 2.048;
public:
    std::vector<double> minBounds; // The minimum bounds for each dimension
    std::vector<double> maxBounds; // The maximum bounds for each dimension
    int nbEvals = 0;
    // const double pi = boost::math::constants::pi<double>();
    const double pi = 3.1416;
    // Constructor
    FitnessFunction();


    //Returns the fitness of one country </summary>
    //<param name="individual"> the solution to evaluate </param>
    //<returns> the fitness </returns>
    virtual double getFitnessValue(std::vector<double> &individual);

};
