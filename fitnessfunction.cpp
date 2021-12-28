#include "fitnessfunction.h"
#define _USE_MATH_DEFINES
FitnessFunction::FitnessFunction()
{
    // Initialize boundaries
    minBounds = std::vector<double>(dimension);
    maxBounds = std::vector<double>(dimension);
    for (int i = 0;i < dimension;i++)
    {
        minBounds[i] = minVal;
        maxBounds[i] = maxVal;
    }
}

double FitnessFunction::getFitnessValue(std::vector<double> &individual)
{
    double fitness = 0;

    // Sphere function
    for (int i = 0; i < individual.size(); i++)
    {
        fitness = fitness + std::pow(individual[i],2);
    }
/*
        // Rastrigin function
        for(int i=0; i<individual.size(); i++)
        {
            fitness = fitness + (pow(individual[i],2)-10*cos(2*pi*individual[i]));
        }
        fitness = 10*dimension + fitness;

        // Rosenbrock function
        for(int i=0; i<individual.size()-1; i++)
        {
            fitness = fitness + 100*pow((pow(individual[i],2)-individual[i+1]),2) + pow((individual[i]-1),2);
        }

        // Ackley function
        double a = 20;
        double b = 0.2;
        double c = 2*pi;
        double s1 = 0;
        double s2 = 0;
        for(int i=0; i<individual.size(); i++)
        {
            s1 = s1 + pow(individual[i],2);
            s2 = s2 + cos(c*individual[i]);
        }
        fitness = -a * exp( -b * sqrt(1/individual.size()*s1)) - exp(1/individual.size()*s2) + a + exp(1);
*/
    nbEvals++;
    return fitness;
}
