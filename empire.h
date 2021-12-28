#pragma once

#include <vector>

// Class creating the empire type, with its imperialists, colonies
//and their respective positions and costs

class Empire
{

    // Empire variables
public:
    int problemDimension;
    std::vector<double> imperialistPosition;
    double imperialistCost = 0;
    std::vector<std::vector<double> > coloniesPosition;
    std::vector<double> coloniesCost;
    double totalCost = 0;


    //<summary>
    //Constructor </summary>
    //<param name="problemDimension"> </param>
    Empire(int problemDimension);

    virtual std::vector<std::vector<double> > doubleVector(int size1, int size2);
    //<summary>
    //To initialize the colonies </summary>
    //<param name="numOfColonies"> </param>
    virtual void init(int numOfColonies);


    // Getters and setters
    virtual std::vector<double> getImperialistPosition();
    virtual void setImperialistPosition(std::vector<double> &imperialistPosition);
    virtual double getImperialistCost();
    virtual void setImperialistCost(double imperialistCost);
    virtual std::vector<std::vector<double> > getColoniesPosition();
    virtual void setColoniesPosition(std::vector<std::vector<double> > &coloniesPosition);
    virtual std::vector<double> getColoniesCost();
    virtual void setColoniesCost(std::vector<double> &coloniesCost);
    virtual double getTotalCost();
    virtual void setTotalCost(double totalCost);
    virtual void setColonyPosition(int colonyIndex, std::vector<double> &position);
    virtual void setColonyCost(int colonyIndex, double cost);


};

