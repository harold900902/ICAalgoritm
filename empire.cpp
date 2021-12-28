#include "empire.h"


Empire::Empire(int problemDimension)
{
    this->problemDimension = problemDimension;

}

std::vector<std::vector<double> > Empire::doubleVector(int size1, int size2)
{
    std::vector<std::vector<double> > newVector(size1);
    for (int vector1 = 0; vector1 < size1; vector1++)
    {
        newVector[vector1] = std::vector<double>(size2);
    }

    return newVector;
}

void Empire::init(int numOfColonies)
{

    this->coloniesPosition = doubleVector(numOfColonies,problemDimension);
    this->coloniesCost= std::vector<double>(numOfColonies);
}

std::vector<double> Empire::getImperialistPosition()
{
    return imperialistPosition;
}

void Empire::setImperialistPosition(std::vector<double> &imperialistPosition)
{
    this->imperialistPosition = imperialistPosition;
}

double Empire::getImperialistCost()
{
    return imperialistCost;
}

void Empire::setImperialistCost(double imperialistCost)
{
    this->imperialistCost = imperialistCost;
}

std::vector<std::vector<double> > Empire::getColoniesPosition()
{
    return coloniesPosition;
}

void Empire::setColoniesPosition(std::vector<std::vector<double> > &coloniesPosition)
{
    this->coloniesPosition = coloniesPosition;
}

std::vector<double> Empire::getColoniesCost()
{
    return coloniesCost;
}

void Empire::setColoniesCost(std::vector<double> &coloniesCost)
{
    this->coloniesCost = coloniesCost;
}

double Empire::getTotalCost()
{
    return totalCost;
}

void Empire::setTotalCost(double totalCost)
{
    this->totalCost = totalCost;
}

void Empire::setColonyPosition(int colonyIndex, std::vector<double> &position)
{
    this->coloniesPosition[colonyIndex] = position;
}

void Empire::setColonyCost(int colonyIndex, double cost)
{
    this->coloniesCost[colonyIndex] = cost;
}
