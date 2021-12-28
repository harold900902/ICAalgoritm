#include "icalgorithm.h"
#include "fitnessfunction.h"
#include "icautils.h"
#include "empire.h"

ICAlgorithm::ICAlgorithm(){}

ICAlgorithm::Actualizar(FitnessFunction *fitnessFunc)
{
    this->fitnessFunc = fitnessFunc;
    this->problemDimension = fitnessFunc->dimension;
    this->minBounds = fitnessFunc->minBounds;
    this->maxBounds = fitnessFunc->maxBounds;
    minimumCost = std::vector<double>(numOfDecades);
    meanCost = std::vector<double>(numOfDecades);
}
std::vector<std::vector<double> > ICAlgorithm::doubleVector(int size1, int size2)
{
    std::vector<std::vector<double> > newVector(size1);
    for (int vector1 = 0; vector1 < size1; vector1++)
    {
        newVector[vector1] = std::vector<double>(size2);
    }

    return newVector;
}

std::vector<int> ICAlgorithm::copyOfRange(std::vector<int> src, int start, int end) {
    int len = end - start;
    std::vector<int> dest(len);
    // note i is always from 0
    for (int i = 0; i < len; i++)
    {
        dest[i] = src[start + i]; // so 0..n = 0+x..n+x
    }
    return dest;
}
std::vector<Empire*> ICAlgorithm::copyOfRangeEmpire(std::vector<Empire *> src, int start, int end) {
    int len = end - start;
    std::vector<Empire*> dest=std::vector<Empire*>(len);
    // note i is always from 0
    for (int i = 0; i < len; i++)
    {
        dest[i] = src[start + i]; // so 0..n = 0+x..n+x
    }
    return dest;
}

void ICAlgorithm::datosFormulario(int numOfCountries, int numOfInitialImperialists,
                                  int numOfDecades,double revolutionRate,double assimilationCoefficient,
                                  double assimilationAngleCoefficient,double zeta,double dampRatio,
                                  double searchPercent)
{
    this->numOfCountries=numOfCountries;
    this->numOfInitialImperialists=numOfInitialImperialists;
    this->numOfAllColonies = numOfCountries - numOfInitialImperialists;
    this->numOfDecades=numOfDecades;
    this->revolutionRate=revolutionRate;
    this->assimilationCoefficient=assimilationCoefficient;
    this->assimilationAngleCoefficient=assimilationAngleCoefficient;
    this->zeta=zeta;
    this->dampRatio=dampRatio;
    this->unitingThreshold=searchPercent;
}
std::vector<double> ICAlgorithm::runICA(int maxEvals)
{

    // Initialize variables
    bestDecadePosition = doubleVector(numOfDecades, problemDimension);
    searchSpaceSize = std::vector<double>(problemDimension);

    // Compute the problem search space, between the min and max bounds
    for (int i = 0; i < problemDimension; i++)
    {
        searchSpaceSize[i] = maxBounds[i] - minBounds[i];
    }
    //utils.printArray("searchSpaceSize", searchSpaceSize);

    // Create an initial population of individuals (countries)
    initialCountries = generateNewCountries(numOfCountries, problemDimension, minBounds, maxBounds);
    //utils.printArray("initialCountries", initialCountries);

    // Compute the cost of each country: the lesser the cost, the more powerful the country is
    initialCosts = getCountriesCosts(initialCountries);
    //utils.printArray("initialCosts", initialCosts);

    // Sort the costs and the corresponding countries in assending order. The best countries will be in higher places.
    sortArray(initialCosts, initialCountries);
    //utils.printArray("initialCountries", initialCountries);
    //utils.printArray("initialCosts", initialCosts);

    // Create the initial empires
    createInitialEmpires();

    int lastDecade = 0;
    // While no stopping condition is met
    for (int decade = 0; decade < numOfDecades; decade++)
    {
        // Check the number of evaluations
        if (fitnessFunc->nbEvals < maxEvals)
        {
//				System.out.println("-------------");
//				System.out.println("Decade: " + decade);
//				System.out.println("Number of empires: " + empiresList.length);
//				System.out.println("Total number of colonies: " + utils.getTotalColoniesCount(empiresList));

            // Update the revolution rate
            revolutionRate = dampRatio * revolutionRate;

            // For each empire
            for (int i = 0; i < empiresList.size(); i++)
            {
                // Assimilation: movement of colonies toward their imperialist
                assimilateColonies(empiresList[i]);

                // Revolution: change the position of some colonies, to avoid getting stuck into local minima
                revolveColonies(empiresList[i]);
                std::vector<std::vector<double> > array=empiresList[i]->getColoniesPosition();
                std::vector<double> costs=getCountriesCosts(array);
                empiresList[i]->setColoniesCost(costs);

                // Empire possession: a strong colony can become the imperialist
                possesEmpire(empiresList[i]);

                // Update the empire's total cost
                  costs=empiresList[i]->getColoniesCost();
                empiresList[i]->setTotalCost(empiresList[i]->getImperialistCost() + zeta * utils->getMean(costs));
            }

            // Uniting Similiar Empires
            uniteSimilarEmpires();

            // Imperialistic Competition
            imperialisticCompetition();

            // If the user wants it, the algorithm can stop when only one empire remains
            if (empiresList.size() == 1 && stopIfJustOneEmpire)
            {
                break;
            }

            // Extract and save results of the round
            std::vector<double> imperialistCosts(empiresList.size());
            for (int i = 0; i < empiresList.size() ; i++)
            {
                imperialistCosts[i] = empiresList[i]->getImperialistCost();
            }

            minimumCost[decade] = imperialistCosts[utils->getMinIndex(imperialistCosts)];
            meanCost[decade] = utils->getMean(imperialistCosts);
            bestDecadePosition[decade] = empiresList[utils->getMinIndex(imperialistCosts)]->getImperialistPosition();

            lastDecade = decade;
        }

    }

    // Extract only the relevant part of the arrays


    std::vector<double> minimumCostRedux (lastDecade+1);
    for (int i = 0; i < lastDecade+1; ++i) {
        minimumCostRedux[i]=minimumCost[i];
    }

    //std::copy(minimumCost.begin(), minimumCost.end() + lastDecade + 1, minimumCostRedux.begin());

    // Return results of the optimization
    //double bestCost = minimumCostRedux[utils.getMinIndex(minimumCostRedux)];
    int bestIndex = utils->getMinIndex(minimumCostRedux);
    std::vector<double> bestSolution = bestDecadePosition[bestIndex];
    //System.out.println("Best solution: " + Arrays.toString(bestSolution));
    //System.out.println("Best fitness: " + bestCost);

    return bestSolution;
}

std::vector<std::vector<double>> ICAlgorithm::generateNewCountries(int numberOfCountries, int dimension, std::vector<double> &minVector, std::vector<double> &maxVector)
{
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] countriesArray = new double[numberOfCountries][dimension];
    std::vector<std::vector<double>> countriesArray = doubleVector(numberOfCountries, dimension);
    double r;
    for (int i = 0; i < numberOfCountries; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            r=seed - ((double)rand()/RAND_MAX);
            countriesArray[i][j] = (maxVector[j] - minVector[j]) * r + minVector[j];
        }
    }
    return countriesArray;
}

std::vector<double> ICAlgorithm::getCountriesCosts(std::vector<std::vector<double>> &countriesArray)
{
    std::vector<double> costsVector(countriesArray.size());
    for (int i = 0; i < countriesArray.size(); i++)
    {
        costsVector[i] = fitnessFunc->getFitnessValue(countriesArray[i]);
    }
    return costsVector;
}

void ICAlgorithm::sortArray(std::vector<double> &arrayToSort, std::vector<std::vector<double>> &matchingArray)
{
    // Create an index array
    std::vector<int> sortOrder = std::vector<int>(arrayToSort.size());
    for (int i = 0; i < sortOrder.size(); i++)
    {
        sortOrder[i] = i;
    }

    // Sort the array using the index array, thanks to a custom comparator
  //  ComparatorAnonymousInnerClass tempVar(this, arrayToSort);
  //  std::sort(sortOrder.begin(),sortOrder.end(),&tempVar);

    // Create copies of the arrays
    std::vector<double> arrayToSortCopy = arrayToSort;
    std::vector<std::vector<double>> matchingArrayCopy = matchingArray;

    // Output the values using the sorted indexes
    for (int i = 0;i < sortOrder.size();i++)
    {
        initialCosts[i] = arrayToSortCopy[sortOrder[i]];
        initialCountries[i] = matchingArrayCopy[sortOrder[i]];
    }
}

ICAlgorithm::ComparatorAnonymousInnerClass::ComparatorAnonymousInnerClass(ICAlgorithm *outerInstance, std::vector<double> &arrayToSort)
{
    this->outerInstance = outerInstance;
    this->arrayToSort = arrayToSort;
}

/* int ICAlgorithm::ComparatorAnonymousInnerClass::compare(boost::optional<int> a, boost::optional<int> b)
{
    double delta = arrayToSort[b] - arrayToSort[a];
    if (delta < 0)
    {
        return 1;
    }
    if (delta > 0)
    {
        return -1;
    }
    return 0;
}*/

void ICAlgorithm::createInitialEmpires()
{

    // Extract the best countries to create empires
    std::vector<std::vector<double>> allImperialistsPosition = utils->extractArrayRange(initialCountries, 0, numOfInitialImperialists);

    // Extract their costs
    std::vector<double> allImperialistsCost(numOfInitialImperialists);
   // System::arraycopy(initialCosts, 0, allImperialistsCost, 0, numOfInitialImperialists);
   // initialCosts=allImperialistsCost;
    for (int i = 0; i < numOfInitialImperialists; ++i) {
        allImperialistsCost[i] = initialCosts[i];
    }
   // allImperialistsCost.insert(allImperialistsCost.begin(),initialCosts.begin(),numOfInitialImperialists);
    //initialCosts.insert(initialCosts.begin(),allImperialistsCost.begin(),allImperialistsCost.end());
    // Extract the rest to create colonies
    std::vector<std::vector<double>> allColoniesPosition = utils->extractArrayRange(initialCountries, numOfInitialImperialists, initialCountries.size());

    // Extract their costs
    std::vector<double> allColoniesCost(initialCosts.size() - numOfInitialImperialists);
    int c=0;
    for (int i = numOfInitialImperialists; i < allColoniesCost.size(); ++i) {
       allColoniesCost[c++] = initialCosts[i];
    }
  //  System::arraycopy(initialCosts, numOfInitialImperialists, allColoniesCost, 0, initialCosts.size() - numOfInitialImperialists);
    //initialCosts.reserve(allImperialistsCost.size()+ allColoniesCost.size());
   // initialCosts.insert(initialCosts.end(),allColoniesCost.begin(),allColoniesCost.end());
    //utils.printArray("allImperialistsPosition", allImperialistsPosition);
    //utils.printArray("allImperialistsCost", allImperialistsCost);
    //utils.printArray("allColoniesPosition", allColoniesPosition);
    //utils.printArray("allColoniesCost", allColoniesCost);

    // Compute the power of imperialists
    std::vector<double> allImperialistsPower(numOfInitialImperialists);
    if (allImperialistsCost[utils->getMaxIndex(allImperialistsCost)] > 0)
    {
        for (int i = 0; i < allImperialistsCost.size(); i++)
        {
            allImperialistsPower[i] = 1.3 * allImperialistsCost[utils->getMaxIndex(allImperialistsCost)] - allImperialistsCost[i];
        }
    }
    else
    {
        for (int i = 0; i < allImperialistsCost.size(); i++)
        {
            allImperialistsPower[i] = 0.7 * allImperialistsCost[utils->getMaxIndex(allImperialistsCost)] - allImperialistsCost[i];
        }
    }
    //utils.printArray("allImperialistsPower", allImperialistsPower);

    // Set the number of colonies for the imperialists
    std::vector<int> allImperialistNumOfColonies(numOfInitialImperialists);
    for (int i = 0; i < allImperialistsPower.size(); i++)
    {
        allImperialistNumOfColonies[i] = static_cast<int>(std::round(allImperialistsPower[i] / utils->getSum(allImperialistsPower) * numOfAllColonies));
    }
  //  std::vector<int> a=copyOfRange(allImperialistNumOfColonies, 0, allImperialistNumOfColonies.size() - 1);
    std::vector<int> a=allImperialistNumOfColonies;
    int sum=utils->getSum(a);
    allImperialistNumOfColonies[allImperialistNumOfColonies.size() - 1] = std::max(numOfAllColonies -sum ,0);
    //utils.printArray("allImperialistNumOfColonies", allImperialistNumOfColonies);

    // Initialize the empires
    empiresList =std::vector<Empire*>(numOfInitialImperialists);
    for (int i = 0; i < numOfInitialImperialists; i++)
    {
        empiresList[i] = new Empire(problemDimension);
    }

    // Create a random permutation of integers
    std::vector<int> randomIndex = utils->randperm(numOfAllColonies);
    std::vector<std::vector<double> > ArrayParts;
    std::vector<double> ArrayPart;
    std::vector<double> costs;
    // Create the empires and attribute them their colonies
    for (int i = 0; i < numOfInitialImperialists; i++)
    {
        std::vector<int> R = copyOfRange(randomIndex, 0, allImperialistNumOfColonies[i]);
        empiresList[i]->init(R.size());
        randomIndex = copyOfRange(randomIndex, allImperialistNumOfColonies[i], randomIndex.size());

        empiresList[i]->setImperialistPosition(allImperialistsPosition[i]);
        empiresList[i]->setImperialistCost(allImperialistsCost[i]);
        ArrayParts=utils->extractGivenArrayParts(allColoniesPosition, R);
        empiresList[i]->setColoniesPosition(ArrayParts);
        ArrayPart=utils->extractGivenArrayParts(allColoniesCost, R);
        empiresList[i]->setColoniesCost(ArrayPart);
        costs=empiresList[i]->getColoniesCost();
        empiresList[i]->setTotalCost(empiresList[i]->getImperialistCost() + zeta * utils->getMean(costs));

        //utils.printEmpire(empiresList[i], i);
    }

    // If an empire has no colony, give it one
    for (int i = 0; i < empiresList.size(); i++)
    {
        if (empiresList[i]->getColoniesPosition().size() == 0)
        {
            ArrayParts.clear();
            ArrayParts =generateNewCountries(1, problemDimension, minBounds, maxBounds);
            empiresList[i]->setColoniesPosition(ArrayParts);
            costs.clear();
            ArrayParts.clear();
            ArrayParts =empiresList[i]->getColoniesPosition();
            costs=getCountriesCosts(ArrayParts);
            empiresList[i]->setColoniesCost(costs);
        }
    }

}

void ICAlgorithm::assimilateColonies(Empire *theEmpire)
{

    // Get the number of colonies of the empire
    int numOfColonies = theEmpire->getColoniesPosition().size();

    // Create an array containing the distance between the imperialist and the colonies
    std::vector<double> aux=theEmpire->getImperialistPosition();
    std::vector<std::vector<double> > repmatArray = utils->repmat(aux,numOfColonies);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] array = new double[numOfColonies][problemDimension];
    std::vector<std::vector<double>> array_Renamed = doubleVector(numOfColonies, problemDimension);
    for (int i = 0; i < numOfColonies; i++)
    {
        for (int j = 0; j < problemDimension; j++)
        {
            array_Renamed[i][j] = repmatArray[i][j] - theEmpire->getColoniesPosition()[i][j];
        }
    }
    //utils.printArray("array",array);

    // Create a new array to store the updated colonies positions
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] coloniesPosition = new double[numOfColonies][problemDimension];
    std::vector<std::vector<double>> coloniesPosition = doubleVector(numOfColonies, problemDimension);
    double r;
    // Fill the array
    for (int i = 0; i < array_Renamed.size(); i++)
    {
        for (int j = 0; j < array_Renamed[0].size(); j++)
        {
            r=seed - ((double)rand()/RAND_MAX);
            coloniesPosition[i][j] = theEmpire->getColoniesPosition()[i][j] + 2 * assimilationCoefficient * r * array_Renamed[i][j];
        }
    }

    // Update the positions
    theEmpire->setColoniesPosition(coloniesPosition);

    // Bound the values with the min and max bounds
    std::vector<std::vector<double>> minVarMatrix = utils->repmat(minBounds,numOfColonies);
    std::vector<std::vector<double>> maxVarMatrix = utils->repmat(maxBounds,numOfColonies);
    std::vector<std::vector<double> > ArrayParts;
    std::vector<std::vector<double> > Max,Min;
    ArrayParts =theEmpire->getColoniesPosition();
    Max=utils->max(ArrayParts,minVarMatrix);
    Min= utils->min(ArrayParts,maxVarMatrix);
    theEmpire->setColoniesPosition(Max);
    theEmpire->setColoniesPosition(Min);
    //utils.printArray("theEmpire.getColoniesPosition()", theEmpire.getColoniesPosition());
}

void ICAlgorithm::revolveColonies(Empire *theEmpire)
{
    // Get the number of colonies to revolve
    int numOfRevolvingColonies = static_cast<int>(std::round((revolutionRate * theEmpire->getColoniesCost().size())));

    // Create a new array with new random positions for the revolving colonies
    std::vector<std::vector<double>> revolvedPosition = generateNewCountries(numOfRevolvingColonies, problemDimension, minBounds, maxBounds);

    // Generate a vector with integer values in a random order
    std::vector<int> R = utils->randperm(theEmpire->getColoniesCost().size());
    R = copyOfRange(R, 0, numOfRevolvingColonies);

    // Update the positions of the revolved colonies of the empire
    for (int i = 0; i < R.size(); i++)
    {
        theEmpire->setColonyPosition(R[i], revolvedPosition[i]);
    }
}

void ICAlgorithm::possesEmpire(Empire *theEmpire)
{
    // Get the costs of the colonies
    std::vector<double> coloniesCost = theEmpire->getColoniesCost();

    // Get the cost of the best colony (the lowest cost)
    int bestColonyInd = utils->getMinIndex(coloniesCost);
    double minColoniesCost = coloniesCost[bestColonyInd];

    // If this cost is lower than the one of the imperialist
    if (minColoniesCost < theEmpire->getImperialistCost())
    {
        // Backup the position and cost of the former imperialist
        std::vector<double> oldImperialistPosition = theEmpire->getImperialistPosition();
        double oldImperialistCost = theEmpire->getImperialistCost();

        // Update the position and cost of the imperialist with the ones of the colony
        theEmpire->setImperialistPosition(theEmpire->getColoniesPosition()[bestColonyInd]);
        theEmpire->setImperialistCost(theEmpire->getColoniesCost()[bestColonyInd]);

        // Update the position and cost of the former colony with the ones of the former imperialist
        theEmpire->setColonyPosition(bestColonyInd, oldImperialistPosition);
        theEmpire->setColonyCost(bestColonyInd, oldImperialistCost);
    }
}

void ICAlgorithm::uniteSimilarEmpires()
{
    // Get the threshold distance between two empires
    double thresholdDistance = unitingThreshold * utils->getNorm(searchSpaceSize);

    // Get the number of empires
    int numOfEmpires = empiresList.size();

    // Compare each empire with the other ones
    for (int i = 0; i < (numOfEmpires - 1); i++)
    {
        for (int j = i + 1; j < numOfEmpires; j++)
        {
            // Compute the distance between the two empires i and j
            std::vector<double> distanceVector(empiresList[i]->getImperialistPosition().size());
            for (int k = 0; k < empiresList[i]->getImperialistPosition().size(); k++)
            {
                distanceVector[k] = empiresList[i]->getImperialistPosition()[k] - empiresList[j]->getImperialistPosition()[k];
            }
            double distance = utils->getNorm(distanceVector);

            // If the empires are too close
            if (distance <= thresholdDistance)
            {
                // Get the best and worst empires of the two
                int betterEmpireInd;
                int worseEmpireInd;
                if (empiresList[i]->getImperialistCost() < empiresList[j]->getImperialistCost())
                {
                    betterEmpireInd = i;
                    worseEmpireInd = j;
                }
                else
                {
                    betterEmpireInd = j;
                    worseEmpireInd = i;
                }

                // Update the positions
                std::vector<std::vector<double>> newColoniesPosition = getColonyPositionsOfUnitedEmpire(betterEmpireInd, worseEmpireInd);
                empiresList[betterEmpireInd]->setColoniesPosition(newColoniesPosition);

                // Update the costs
                std::vector<double> newColoniesCost = getColonyCostsOfUnitedEmpire(betterEmpireInd, worseEmpireInd);
                empiresList[betterEmpireInd]->setColoniesCost(newColoniesCost);

                // Update the total cost of the united empire
                 std::vector<double> costs=empiresList[betterEmpireInd]->getColoniesCost();
                empiresList[betterEmpireInd]->setTotalCost(empiresList[betterEmpireInd]->getImperialistCost() + zeta * utils->getMean(costs));

                // Update the empires list
                deleteAnEmpire(worseEmpireInd);
                //System.out.println("New number of empires: " + empiresList.length);

                return;
            }

        }
    }
}

std::vector<double> ICAlgorithm::getColonyCostsOfUnitedEmpire(int betterEmpireInd, int worseEmpireInd)
{
    // Get the new number of colonies of the united empire
    int newColoniesCount = empiresList[betterEmpireInd]->getColoniesCost().size() + 1 + empiresList[worseEmpireInd]->getColoniesCost().size();

    // Create a new vector to store the costs of the colonies
    std::vector<double> newColoniesCost(newColoniesCount);

    // At first, store the costs of the colonies of the best empire in the vector
    int i;
    for (i = 0; i < empiresList[betterEmpireInd]->getColoniesCost().size(); i++)
    {
        newColoniesCost[i] = empiresList[betterEmpireInd]->getColoniesCost()[i];
    }

    // Then add the cost of the former worst imperialist
    newColoniesCost[i] = empiresList[worseEmpireInd]->getImperialistCost();

    // Finally, add the costs of the colonies of the worst empire
    int i2;
    for (i2 = i + 1; i2 < newColoniesCount; i2++)
    {
        newColoniesCost[i2] = empiresList[worseEmpireInd]->getColoniesCost()[i2 - empiresList[betterEmpireInd]->getColoniesCost().size() - 1];
    }

    // Return the vector with the updated costs
    return newColoniesCost;
}

std::vector<std::vector<double>> ICAlgorithm::getColonyPositionsOfUnitedEmpire(int betterEmpireInd, int worseEmpireInd)
{
    // Get the new number of colonies of the united empire
    int newSize = empiresList[betterEmpireInd]->getColoniesPosition().size() + 1 + empiresList[worseEmpireInd]->getColoniesPosition().size();

    // Create a new array to store the positions of the colonies
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] newColoniesPosition = new double[newSize][problemDimension];
    std::vector<std::vector<double>> newColoniesPosition = doubleVector(newSize, problemDimension);

    // At first, store the positions of the colonies of the best empire in the array
    int i;
    for (i = 0; i < empiresList[betterEmpireInd]->getColoniesPosition().size(); i++)
    {
        newColoniesPosition[i] = empiresList[betterEmpireInd]->getColoniesPosition()[i];
    }

    // Then add the position of the former worst imperialist
    newColoniesPosition[i] = empiresList[worseEmpireInd]->getImperialistPosition();

    // Finally, add the costs of the colonies of the worst empire
    int i2;
    for (i2 = i + 1; i2 < newSize; i2++)
    {
        newColoniesPosition[i2] = empiresList[worseEmpireInd]->getColoniesPosition()[i2 - empiresList[betterEmpireInd]->getColoniesPosition().size() - 1];
    }

    // Return the array with the updated positions
    return newColoniesPosition;

}

void ICAlgorithm::imperialisticCompetition()
{

    // Generate a random number, and return if this number is too high
    double ran=seed - ((double)rand()/RAND_MAX);
    if (ran > .11)
    {
        return;
    }

    // Idem if their is only one empire
    if (empiresList.size() <= 1)
    {
        return;
    }

    // Get the total cost of each empire
    std::vector<double> totalCosts(empiresList.size());
    for (int i = 0; i < empiresList.size(); i++)
    {
        totalCosts[i] = empiresList[i]->getTotalCost();
    }
    //utils.printArray("totalCosts", totalCosts);

    // Get the weakest empire (the one with the highest cost) and its cost
    int weakestEmpireInd = utils->getMaxIndex(totalCosts);
    double maxTotalCost = totalCosts[weakestEmpireInd];

    // Get the power of each empire
    std::vector<double> totalPowers(empiresList.size());
    for (int i = 0; i < empiresList.size(); i++)
    {
        totalPowers[i] = maxTotalCost - totalCosts[i];
    }
    //utils.printArray("totalPowers", totalPowers);

    // Get the possession probability of each empire
    std::vector<double> possessionProbability(empiresList.size());
    for (int i = 0; i < empiresList.size(); i++)
    {
        possessionProbability[i] = totalPowers[i] / utils->getSum(totalPowers);
    }
    //utils.printArray("possessionProbability", possessionProbability);

    // Select an empire according to their probabilities
    int selectedEmpireInd = selectAnEmpire(possessionProbability);
    //System.out.println("selectedind: " + selectedEmpireInd);

    // Generate a random integer
    int numOfColoniesOfWeakestEmpire = empiresList[weakestEmpireInd]->getColoniesCost().size();
    int indexOfSelectedColony =rand()%numOfColoniesOfWeakestEmpire;
    // Update the positions of the colonies of the selected empire
    // by adding the position of the randomly selected colony of the weakest empire
    std::vector<std::vector<double>> Position =empiresList[selectedEmpireInd]->getColoniesPosition();
    std::vector<double> Colony = empiresList[weakestEmpireInd]->getColoniesPosition()[indexOfSelectedColony];
    std::vector<std::vector<double>> ColonyPosition = concatenatePositions(Position,Colony);
    empiresList[selectedEmpireInd]->setColoniesPosition(ColonyPosition);

    // Idem for the costs
    std::vector<double> Costs = empiresList[selectedEmpireInd]->getColoniesCost();
    double Col = empiresList[weakestEmpireInd]->getColoniesCost()[indexOfSelectedColony];
    std::vector<double> ColonyCosts = concatenateCosts(Costs,Col);
    empiresList[selectedEmpireInd]->setColoniesCost(ColonyCosts);

    // Update the positions of the colonies of the weakest empire
    // by removing the position of the randomly selected colony of the empire
    Position.clear();
    Position = empiresList[weakestEmpireInd]->getColoniesPosition();
    ColonyPosition.clear();
    ColonyPosition = removeColonyPosition(Position, indexOfSelectedColony);
    empiresList[weakestEmpireInd]->setColoniesPosition(ColonyPosition);

    // Idem for the costs
    Costs.clear();
    Costs = empiresList[weakestEmpireInd]->getColoniesCost();
    ColonyCosts.clear();
    ColonyCosts = removeColonyCost(Costs, indexOfSelectedColony);
    empiresList[weakestEmpireInd]->setColoniesCost(ColonyCosts);

    // Get the number of colonies of the weakest empire
    numOfColoniesOfWeakestEmpire = empiresList[weakestEmpireInd]->getColoniesCost().size();

    // If it has not more than 1 colony, then make it disapear/collapse
    // It is then absorbed by the selected empire
    if (numOfColoniesOfWeakestEmpire <= 1)
    {
        // Update the positions of the colonies by adding the collapsed imperialist
        Position.clear();
        Position = empiresList[selectedEmpireInd]->getColoniesPosition();
        std::vector<double> Empire =  empiresList[weakestEmpireInd]->getImperialistPosition();
        std::vector<std::vector<double>>  EmpirePosition = concatenatePositions(Position,Empire);
        empiresList[selectedEmpireInd]->setColoniesPosition(EmpirePosition);

        // Idem for the costs
        Costs.clear();
        Costs = empiresList[selectedEmpireInd]->getColoniesCost();
        std::vector<double> EmpireCosts = concatenateCosts(Costs,empiresList[weakestEmpireInd]->getImperialistCost());
        empiresList[selectedEmpireInd]->setColoniesCost(EmpireCosts);

        // Erase the collapsed empire from the empires list
        deleteAnEmpire(weakestEmpireInd);
        //System.out.println("An empire has collapsed");
        //System.out.println("New number of empires: " + empiresList.length);
    }

}

std::vector<std::vector<double>> ICAlgorithm::removeColonyPosition(std::vector<std::vector<double>> &colonyPositions, int indexToRemove)
{
    // Create a new array to store the updated positions
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] newColonyPositions = new double[colonyPositions.length-1][colonyPositions[0].length];
    std::vector<std::vector<double>> newColonyPositions = doubleVector(colonyPositions.size() - 1, colonyPositions[0].size());

    // Copy in it the positions before the colony to remove
    for (int i = 0; i < indexToRemove; i++)
    {
        newColonyPositions[i] = colonyPositions[i];
    }

    // Then copy the rest of the positions, without including to colony to remove
    for (int j = indexToRemove; j < newColonyPositions.size(); j++)
    {
        newColonyPositions[j] = colonyPositions[j + 1];
    }

    // Return the updated positions
    return newColonyPositions;
}

std::vector<double> ICAlgorithm::removeColonyCost(std::vector<double> &colonyCosts, int indexToRemove)
{
    // Create a new vector to store the updated costs
    std::vector<double> newColonyCosts(colonyCosts.size() - 1);

    // Copy in it the costs before the colony to remove
    for (int i = 0; i < indexToRemove; i++)
    {
        newColonyCosts[i] = colonyCosts[i];
    }

    // Then copy the rest of the costs, without including to colony to remove
    for (int j = indexToRemove; j < newColonyCosts.size(); j++)
    {
        newColonyCosts[j] = colonyCosts[j + 1];
    }

    // Return the updated costs
    return newColonyCosts;
}

std::vector<std::vector<double>> ICAlgorithm::concatenatePositions(std::vector<std::vector<double>> &positions1, std::vector<double> &position2)
{
    // Create a new array to store the updated positions
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: double[][] newPositions = new double[positions1.length+1][positions1[0].length];
    std::vector<std::vector<double>> newPositions = doubleVector(positions1.size() + 1, positions1[0].size());

    // Add the positions of the existing empire in the array
    int i;
    for (i = 0; i < positions1.size(); i++)
    {
        newPositions[i] = positions1[i];
    }

    // Then add the position to add at the end
    newPositions[i] = position2;

    // Return the updated positions
    return newPositions;
}

std::vector<double> ICAlgorithm::concatenateCosts(std::vector<double> &costs1, double cost2)
{
    // Create a new vector to store the updated costs
    std::vector<double> newCosts(costs1.size() + 1);

    // Add the costs of the existing empire in the array
    int i;
    for (i = 0; i < costs1.size(); i++)
    {
        newCosts[i] = costs1[i];
    }

    // Then add the cost to add at the end
    newCosts[i] = cost2;

    // Return the updated costs
    return newCosts;
}

void ICAlgorithm::deleteAnEmpire(int indexToDelete)
{
    // Split the empires list into two sub lists, before and after the empire to remove
    std::vector<Empire*> empiresList1 = copyOfRangeEmpire(empiresList, 0, indexToDelete);
    std::vector<Empire*> empiresList2 = copyOfRangeEmpire(empiresList, indexToDelete+1, empiresList.size());

    // Create a new list with the updated size
    empiresList = std::vector<Empire*>(empiresList1.size() + empiresList2.size());

    // Copy the empires of the sub lists into the new one
    for (int n = 0; n < (empiresList1.size() + empiresList2.size()); n++)
    {
        if (n < empiresList1.size())
        {
            empiresList[n] = empiresList1[n];
        }

        if (n >= empiresList1.size())
        {
            empiresList[n] = empiresList2[n - empiresList1.size()];
        }
    }
}

int ICAlgorithm::selectAnEmpire(std::vector<double> &probability)
{
    double r;
    // Create a vector of random numbers
    std::vector<double> randVector(probability.size());
    for (int i = 0; i < probability.size(); i++)
    {
       r=seed - ((double)rand()/RAND_MAX);
        randVector[i] = r;
    }

    // Substract to each element of this vector the corresponding
    // value of the probability vector
    std::vector<double> dVector(probability.size());
    for (int i = 0; i < probability.size(); i++)
    {
        dVector[i] = probability[i] - randVector[i];
    }

    // Return the index of the maximum value of the vector
    return utils->getMaxIndex(dVector);
}

void ICAlgorithm::reset()
{
    seed = TIME_MS;
    empiresList = std::vector<Empire*>(numOfInitialImperialists); // List of Empires
    minimumCost = std::vector<double>(numOfDecades); // The minimum cost of each decade
    meanCost = std::vector<double>(numOfDecades); // The mean cost of each decade
    fitnessFunc->nbEvals = 0;
}

std::wstring ICAlgorithm::getDetails()
{
    return std::wstring(L"Imperialist Competitive Algorithm (ICA): ") +
    L"as described in: Atashpaz-Gargari, E. and Lucas, C., Imperialist Competitive Algorithm: An Algorithm for Optimization Inspired by Imperialistic Competition, IEEE Congress on Evolutionary Computation, 2007, pp. 4661-4667." +
    L" Adapted from: http://www.mathworks.com/matlabcentral/fileexchange/22046-imperialist-competitive-algorithm-ica";
}

std::wstring ICAlgorithm::getName()
{
    return L"Imperialist Competitive Algorithm";
}
