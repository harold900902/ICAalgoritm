#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include "empire.h"
/*
 * Copyright 2011, Robin Roche
 * This file is part of jica.

    jica is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    jica is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with jica.  If not, see <http://www.gnu.org/licenses/>.
*/




/// <summary>
/// Contains several methos on arrays used by the ICA algorithm
/// @author Robin Roche
/// </summary>
class ICAUtils
{

    /// <summary>
    /// Returns the index of the max value contained in the vector </summary>
    /// <param name="vector"> values </param>
    /// <returns> the index of the max value </returns>
public:
    virtual int getMaxIndex(std::vector<double> &vector);



    /// <summary>
    /// Returns the index of the min value contained in the vector </summary>
    /// <param name="vector"> values </param>
    /// <returns> the index of the min value </returns>
    virtual int getMinIndex(std::vector<double> &vector);



    /// <summary>
    /// Returns the mean value of a vector </summary>
    /// <param name="vector"> the vector </param>
    /// <returns> the mean value </returns>
    virtual double getMean(std::vector<double> &vector);



    /// <summary>
    /// Returns the norm of a vector </summary>
    /// <param name="vector"> the vector </param>
    /// <returns> the norm </returns>
    virtual double getNorm(std::vector<double> &vector);



    /// <summary>
    /// Returns the sum of the elements on a vector </summary>
    /// <param name="vector"> the vector </param>
    /// <returns> the sum </returns>
    virtual double getSum(std::vector<double> &vector);



    /// <summary>
    /// Returns the sum of the elements on a vector </summary>
    /// <param name="vector"> the vector </param>
    /// <returns> the sum </returns>
    virtual int getSum(std::vector<int> &vector);



    /// <summary>
    /// Returns an array with the maximum values of two two-dimensional arrays </summary>
    /// <param name="array1"> the first array </param>
    /// <param name="array2"> the second array </param>
    /// <returns> an array with the max values </returns>
    virtual std::vector<std::vector<double> > max(std::vector<std::vector<double> > &array1, std::vector<std::vector<double> > &array2);


    virtual std::vector<std::vector<double> > doubleVector(int size1, int size2);
    /// <summary>
    /// Returns an array with the minimum values of two two-dimensional arrays </summary>
    /// <param name="array1"> the first array </param>
    /// <param name="array2"> the second array </param>
    /// <returns> an array with the min values </returns>
    virtual std::vector<std::vector<double> > min(std::vector<std::vector<double> > &array1, std::vector<std::vector<double> > &array2);



    /// <summary>
    /// Returns a vector with the n integers (each appearing once) in a random order
    /// This is equivalent to the Matlab function randperm() </summary>
    /// <param name="n"> the number of values </param>
    /// <param name="r"> the random generator </param>
    /// <returns> the vector of integers </returns>
    virtual std::vector<int> randperm(int n);



    /// <summary>
    /// Returns an array with a copy of a pattern, done n times
    /// This is equivalent to the Matlab function repmat() </summary>
    /// <param name="pattern"> the pattern to to repeat </param>
    /// <param name="n"> the number of times </param>
    /// <returns> the array with the copies </returns>
    virtual std::vector<std::vector<double> > repmat(std::vector<double> &pattern, int n);



    /// <summary>
    /// Returns an extract of an array between two indexes (i.e. a range of it) </summary>
    /// <param name="array"> the array </param>
    /// <param name="startIndex"> the index where to start </param>
    /// <param name="endIndex"> the index where to stop </param>
    /// <returns> the array extract </returns>
    virtual std::vector<std::vector<double> > extractArrayRange(std::vector<std::vector<double> > &array_Renamed, int startIndex, int endIndex);



    /// <summary>
    /// Returns an extract of an array, with only selected indexes extracted </summary>
    /// <param name="array"> the array to be extracted from </param>
    /// <param name="selectedIndexes"> the indexes to extract data from </param>
    /// <returns> the array with the extracted data </returns>
    virtual std::vector<std::vector<double> > extractGivenArrayParts(std::vector<std::vector<double> > &array_Renamed, std::vector<int> &selectedIndexes);



    /// <summary>
    /// Returns an extract of an array, with only selected indexes extracted </summary>
    /// <param name="array"> the array to be extracted from </param>
    /// <param name="selectedIndexes"> the indexes to extract data from </param>
    /// <returns> the array with the extracted data </returns>
    virtual std::vector<double> extractGivenArrayParts(std::vector<double> &array_Renamed, std::vector<int> &selectedIndexes);



    /// <summary>
    /// Prints the values of an array </summary>
    /// <param name="arrayName"> </param>
    /// <param name="array"> </param>
    virtual void printArray(std::string arrayName, std::vector<double> &array_Renamed);



    /// <summary>
    /// Prints the values of an array </summary>
    /// <param name="arrayName"> </param>
    /// <param name="array"> </param>
    virtual void printArray2(std::string arrayName, std::vector<std::vector<double> > &array_Renamed);



    /// <summary>
    /// Prints the values of an array </summary>
    /// <param name="arrayName"> </param>
    /// <param name="array"> </param>
  //  virtual void printArray(std::string &arrayName, std::vector<int> &array_Renamed);



    /// <summary>
    /// Prints the characteristics of an empire </summary>
    /// <param name="empire"> </param>
    virtual void printEmpire(Empire *empire, int empireIndex);



    /// <summary>
    /// Returns the total number of colonies in the empires list </summary>
    /// <param name="empiresList"> </param>
    /// <returns> the number of colonies </returns>
    virtual int getTotalColoniesCount(std::vector<Empire*> &empiresList);

};
