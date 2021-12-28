#include "icautils.h"
#include <iostream>
#include <sstream>
int ICAUtils::getMaxIndex(std::vector<double> &vector)
{
    double max = vector[0];
    int i;
    int bestIndex = 0;
    for (i = 1; i < vector.size(); i++)
    {
        if (vector[i] > max)
        {
            max = vector[i];
            bestIndex = i;
        }
    }
    return bestIndex;
}

int ICAUtils::getMinIndex(std::vector<double> &vector)
{
    double min = std::numeric_limits<double>::max();
    int i;
    int bestIndex = 0;
    for (i = 0; i < vector.size(); i++)
    {
        if (vector[i] < min)
        {
            min = vector[i];
            bestIndex = i;
        }
    }
    return bestIndex;
}


double ICAUtils::getMean(std::vector<double> &vector)
{
    double sum = 0;
    for (int i = 0; i < vector.size(); i++)
    {
        sum += vector[i];
    }
    return sum / vector.size();
}

double ICAUtils::getNorm(std::vector<double> &vector)
{
    double sum = 0;
    for (int i = 0; i < vector.size(); i++)
    {
        sum = sum + std::pow(vector[i],2);
    }
    return std::sqrt(sum);
}

double ICAUtils::getSum(std::vector<double> &vector)
{
    double sum = 0;
    for (auto i : vector)
    {
        sum += i;
    }
    return sum;
}

int ICAUtils::getSum(std::vector<int> &vector)
{
    int sum = 0;
    for (auto i : vector)
    {
        sum += i;
    }
    return sum;
}

std::vector<std::vector<double>> ICAUtils::max(std::vector<std::vector<double>> &array1, std::vector<std::vector<double>> &array2)
{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double maxArray[][] = new double[array1.length][array1[0].length];
    std::vector<std::vector<double>> maxArray = doubleVector(array1.size(), array1[0].size());

    for (int i = 0; i < array1.size(); i++)
    {
        for (int j = 0; j < array1[0].size(); j++)
        {
            maxArray[i][j] = std::max(array1[i][j], array2[i][j]);
        }
    }
    return maxArray;
}
std::vector<std::vector<double> > ICAUtils::doubleVector(int size1, int size2)
{
    std::vector<std::vector<double> > newVector(size1);
    for (int vector1 = 0; vector1 < size1; vector1++)
    {
        newVector[vector1] = std::vector<double>(size2);
    }

    return newVector;
}
std::vector<std::vector<double>> ICAUtils::min(std::vector<std::vector<double>> &array1, std::vector<std::vector<double>> &array2)
{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double minArray[][] = new double[array1.length][array1[0].length];

    std::vector<std::vector<double>> minArray = doubleVector(array1.size(), array1[0].size());
    for (int i = 0; i < array1.size(); i++)
    {
        for (int j = 0; j < array1[0].size(); j++)
        {
            minArray[i][j] = std::min(array1[i][j], array2[i][j]);
        }
    }
    return minArray;
}

std::vector<int> ICAUtils::randperm(int n)
{
    std::vector<int> nVector;
    for (int i = 0; i < n; i++)
    {
        nVector.push_back(i);
    }

    std::vector<int> outputVector(n);
    int outputIndex = 0;

    while (nVector.size() > 0)
    {
        int position = rand()%nVector.size() ;
        outputVector[outputIndex] = nVector[position];
        outputIndex++;
        nVector.erase(nVector.begin() + position);
    }

    return outputVector;
}

std::vector<std::vector<double>> ICAUtils::repmat(std::vector<double> &pattern, int n)
{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] outputArray = new double[n][pattern.length];
    std::vector<std::vector<double>> outputArray = doubleVector(n, pattern.size());
    for (int i = 0; i < n; i++)
    {
        outputArray[i] = pattern;
    }
    return outputArray;
}

std::vector<std::vector<double>> ICAUtils::extractArrayRange(std::vector<std::vector<double>> &array_Renamed, int startIndex, int endIndex)
{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] arrayExtract = new double[endIndex-startIndex][array[0].length];
    std::vector<std::vector<double>> arrayExtract = doubleVector(endIndex - startIndex, array_Renamed[0].size());
    int newIndex = 0;
    for (int i = startIndex; i < endIndex ; i++)
    {
        arrayExtract[newIndex] = array_Renamed[i];
        newIndex++;
    }
    return arrayExtract;
}

std::vector<std::vector<double>> ICAUtils::extractGivenArrayParts(std::vector<std::vector<double>> &array_Renamed, std::vector<int> &selectedIndexes)
{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] arrayExtract = new double[selectedIndexes.length][array[0].length];
    std::vector<std::vector<double>> arrayExtract = doubleVector(selectedIndexes.size(), array_Renamed[0].size());
    int index;
    for (int i = 0; i < selectedIndexes.size(); i++)
    {
        index = selectedIndexes[i];
        arrayExtract[i] = array_Renamed[index];
    }
    return arrayExtract;
}

std::vector<double> ICAUtils::extractGivenArrayParts(std::vector<double> &array_Renamed, std::vector<int> &selectedIndexes)
{
    std::vector<double> arrayExtract(selectedIndexes.size());
    int index;
    for (int i = 0; i < selectedIndexes.size(); i++)
    {
        index = selectedIndexes[i];
        arrayExtract[i] = array_Renamed[index];
    }
    return arrayExtract;
}

void ICAUtils::printArray(std::string arrayName, std::vector<double> &array_Renamed)
{
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
   // std::stringstream result;
  //  std::copy(array_Renamed.begin(), array_Renamed.end(), std::ostream_iterator<int>(result, " "));
   /* std::ostringstream StringRepresentation;
    for ( std::vector<int>::iterator it = array_Renamed.begin(); it != array_Renamed.end(); it++ ) {
        StringRepresentation << *it << " ";
    }
    std::wcout << arrayName << L": " <<StringRepresentation << std::endl;*/
}

void ICAUtils::printArray2(std::string arrayName, std::vector<std::vector<double>> &array_Renamed)
{
  /*  for (int i = 0; i < array_Renamed.size(); i++)
    {
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
        std::wcout << arrayName << "[" << i << "]: " << Arrays->toString(array_Renamed[i]) << std::endl;
    }*/
}

/*void ICAUtils::printArray(std::string &arrayName, std::vector<int> &array_Renamed)
{
//JAVA TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'toString':
    std::wcout << arrayName << L": " << Arrays->toString(array_Renamed) << std::endl;
}*/

void ICAUtils::printEmpire(Empire *empire, int empireIndex)
{
    std::vector<double> EmpirePosition =  empire->getImperialistPosition();
    std::vector<std::vector<double> > ColonyPosition = empire->getColoniesPosition();
    std::vector<double> ColonyCost = empire->getColoniesCost();
    std::wcout << "Empire " << empireIndex << std::endl;
    std::wcout << "Number of colonies: " << empire->getColoniesCost().size() << std::endl;
    printArray("imperialistPosition",EmpirePosition);
    std::wcout << "imperialistCost: " << empire->getImperialistCost() << std::endl;
    printArray2("coloniesPosition", ColonyPosition);
    printArray("coloniesCost",ColonyCost);
    std::wcout << "totalCost: " << empire->getTotalCost() << std::endl;
}

int ICAUtils::getTotalColoniesCount(std::vector<Empire*> &empiresList)
{
    int currentNumOfColonies = 0;
    for (int i = 0; i < empiresList.size(); i++)
    {
        currentNumOfColonies = currentNumOfColonies + empiresList[i]->getColoniesPosition().size();
    }
    return currentNumOfColonies;
}
