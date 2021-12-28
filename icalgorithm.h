#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <sys/time.h>
#include <windows.h>
#include <empire.h>
#include <ICAUtils.h>
#include <fitnessfunction.h>
#include <array>
using namespace std;

//#include <boost/optional/optional.hpp>

// This class contains the ICA algorithm methods


class ICAlgorithm
{
    // ICA parameters
public:
    int numOfCountries = 20;					// Number of initial countries
    int numOfInitialImperialists = 2;			// Number of initial imperialists
    int numOfAllColonies = numOfCountries - numOfInitialImperialists;
    int numOfDecades = 600;					// Number of decades (generations)
    double revolutionRate = 0.1;				// Revolution is the process in which the socio-political characteristics of a country change suddenly
    double assimilationCoefficient = 2;			// In the original paper assimilation coefficient is shown by "beta"
    double assimilationAngleCoefficient = .5;   // In the original paper assimilation angle coefficient is shown by "gama"
    double zeta = 0.02;							// Total Cost of Empire = Cost of Imperialist + Zeta * mean(Cost of All Colonies)
    double dampRatio = 0.99;					// The damp ratio
    bool stopIfJustOneEmpire = false;			// Use "true" to stop the algorithm when just one empire is remaining. Use "false" to continue the algorithm
    double unitingThreshold = 0.02;				// The percent of search space size, which enables the uniting process of two empires


    // Variables
protected:
  //  long seed = currentTimeMillis();
    double seed = TIME_MS;
public:
    //Random *r = new Random(seed);
    int problemDimension = 0; // Problem dimension
    std::vector<double> minBounds; // Minimum bounds
    std::vector<double> maxBounds; // Maximum bounds
//	std::vector<Empire*> empiresList(numOfInitialImperialists); // List of Empires
    std::vector<Empire*> empiresList; // List of Empires

    std::vector<std::vector<double> > initialCountries; // The initial countries with their positions
    std::vector<double> initialCosts; // The costs of the initial countries
    std::vector<std::vector<double> > bestDecadePosition; // The best found position for each decade
    //std::vector<double> minimumCost(numOfDecades); // The minimum cost of each decade
    //std::vector<double> meanCost(numOfDecades); // The mean cost of each decade
    std::vector<double> minimumCost; // The minimum cost of each decade
    std::vector<double> meanCost; // The mean cost of each decade
    std::vector<double> searchSpaceSize; // The search space size (between the min and max bounds)
    ICAUtils *utils = new ICAUtils(); // A class with useful methods for array operations
    FitnessFunction *fitnessFunc; // A class with the fitness function



    /// <summary>
    /// Constructor of the class </summary>
    /// <param name="args"> an object array with the parameters
    /// The first is the problem dimension
    /// The second a vector with the min bounds
    /// The third a vector with the max bounds </param>
    virtual ~ICAlgorithm()
    {
        //delete r;
        delete fitnessFunc;
    }
    ICAlgorithm();


public:
    Actualizar(FitnessFunction *fitnessFunc);
    std::vector<std::vector<double> > doubleVector(int size1, int size2);
    std::vector<int> copyOfRange (std::vector<int> src, int start, int end);
    std::vector<Empire *> copyOfRangeEmpire(std::vector<Empire*> src, int start, int end);
    /// <summary>
    /// Runs the ICA algorithm </summary>
    /// <returns> the best found solution </returns>
    void datosFormulario(int numOfCountries, int numOfInitialImperialists,
                                      int numOfDecades,double revolutionRate,double assimilationCoefficient,
                                      double assimilationAngleCoefficient,double zeta,double dampRatio,
                                      double searchPercent);
     std::vector<double> runICA(int maxEvals);

private:


     /// <summary>
     /// Generates new countries </summary>
     /// <param name="numberOfCountries"> the number of countries to generate </param>
     /// <param name="dimension"> the dimension of each country </param>
     /// <param name="minVector"> the minimum values for each dimension </param>
     /// <param name="maxVector"> the maximum values for each dimension </param>
     /// <param name="rand"> a random number generator </param>
     /// <returns> an array with the new countries positions </returns>
    std::vector<std::vector<double> > generateNewCountries(int numberOfCountries, int dimension, std::vector<double> &minVector, std::vector<double> &maxVector);



    /// <summary>
    /// Returns a vector with the cost of all countries computed according to their position </summary>
    /// <param name="numberOfCountries"> the number of countries </param>
    /// <param name="countriesArray"> </param>
    /// <returns> a vector with the costs of all countries </returns>
    std::vector<double> getCountriesCosts(std::vector<std::vector<double> > &countriesArray);



    // TODO: directly operate on the arrays, not copies?
    /// <summary>
    /// Sorts an array according to its values and sorts another array in the same order
    /// The lowest value is put first </summary>
    /// <param name="arrayToSort"> the array to sort according to its values </param>
    /// <param name="matchingArray"> the array that should be sorted according to the first one </param>
    void sortArray(std::vector<double> &arrayToSort, std::vector<std::vector<double> > &matchingArray);
//: public Comparator <int>
private:
    class ComparatorAnonymousInnerClass
    {
    private:
        ICAlgorithm *outerInstance;

        std::vector<double> arrayToSort;

    public:
        ComparatorAnonymousInnerClass(ICAlgorithm *outerInstance, std::vector<double> &arrayToSort);

      //  virtual int compare(boost::optional<int> a, boost::optional<int> b);
    };



    /// <summary>
    /// Generates the initial empires
    /// </summary>
private:
    void createInitialEmpires();



    /// <summary>
    /// Assimilates the colonies of an empire: move their positions </summary>
    /// <param name="theEmpire"> </param>
    void assimilateColonies(Empire *theEmpire);



    /// <summary>
    /// Make colonies of an empire revolve.
    /// This is equivalent to a perturbation which avoid getting stuck
    /// into local minima. </summary>
    /// <param name="theEmpire"> to revolve </param>
    void revolveColonies(Empire *theEmpire);



    /// <summary>
    /// Can make a colony become the imperialist
    /// if it is more powerful than the imperialist. </summary>
    /// <param name="theEmpire"> </param>
    void possesEmpire(Empire *theEmpire);



    /// <summary>
    /// Unites imperialists that are close to each other
    /// </summary>
    void uniteSimilarEmpires();



    /// <summary>
    /// Returns the costs of the colonies of the united empire (after two empires merge) </summary>
    /// <param name="betterEmpireInd"> the best empire </param>
    /// <param name="worseEmpireInd"> the worst empire </param>
    /// <returns> the corresponding colony costs </returns>
    std::vector<double> getColonyCostsOfUnitedEmpire(int betterEmpireInd, int worseEmpireInd);



    /// <summary>
    /// Returns the positions of the colonies of the united empire (after two empires merge) </summary>
    /// <param name="betterEmpireInd"> the best empire </param>
    /// <param name="worseEmpireInd"> the worst empire </param>
    /// <returns> the corresponding colony positions </returns>
    std::vector<std::vector<double> > getColonyPositionsOfUnitedEmpire(int betterEmpireInd, int worseEmpireInd);



    /// <summary>
    /// Runs the competition between empires
    /// </summary>
    void imperialisticCompetition();



    /// <summary>
    /// Removes a position from the colony positions array </summary>
    /// <param name="colonyPositions"> </param>
    /// <param name="indexToRemove"> </param>
    /// <returns> the updated positions </returns>
    std::vector<std::vector<double> > removeColonyPosition(std::vector<std::vector<double> > &colonyPositions, int indexToRemove);



    /// <summary>
    /// Removes a position from the colony costs vector </summary>
    /// <param name="colonyCosts"> </param>
    /// <param name="indexToRemove"> </param>
    /// <returns> the updated costs vector </returns>
    std::vector<double> removeColonyCost(std::vector<double> &colonyCosts, int indexToRemove);



    /// <summary>
    /// Concatenates the positions of an empire with an additionnal one </summary>
    /// <param name="positions1"> the positions array of the empire </param>
    /// <param name="position2"> the position to add </param>
    /// <returns> the updated positions </returns>
    std::vector<std::vector<double> > concatenatePositions(std::vector<std::vector<double> > &positions1, std::vector<double> &position2);



    /// <summary>
    /// Concatenates the costs of an empire with an additionnal one </summary>
    /// <param name="costs1"> the costs vector of the empire </param>
    /// <param name="cost2"> the cost to add </param>
    /// <returns> the updated costs </returns>
    std::vector<double> concatenateCosts(std::vector<double> &costs1, double cost2);



    /// <summary>
    /// Deletes an empire from the empires list </summary>
    /// <param name="indexToDelete"> </param>
    void deleteAnEmpire(int indexToDelete);



    /// <summary>
    /// Selects an empire according to their probabilities </summary>
    /// <param name="probability"> the probability vector </param>
    /// <returns> the selected empire index </returns>
    int selectAnEmpire(std::vector<double> &probability);



    /// <summary>
    /// Resets the variables for the next run
    /// </summary>
public:
    virtual void reset();



    /// <summary>
    /// Returns a string with informtion about the algorithm </summary>
    /// <returns> the string </returns>
    virtual std::wstring getDetails();



    /// <summary>
    /// Returns a string with the name of the algorithm </summary>
    /// <returns> the string </returns>
    virtual std::wstring getName();

};
