// Advanced Computer Programming: AERSP 424
// Homework 1 Spring 2024.cpp 
// Svetoslav Trayanov 
// 02/11/2024
//**********************************************************************************************************//

#include <iostream>
#include <iomanip>
#include <vector>				// For output formatting
#include <tuple>				// To return multiple values from function.

   
    /***********************************
     std::cout << "Enter the weight of each passenger. Enter a non-numeric value to finish:\n";

    while (std::cin >> weight) {
        passengerWeights.push_back(weight);
        totalWeight += weight;
    }

    int numPassengers = passengerWeights.size();

    std::cout << "Total number of passengers: " << numPassengers << std::endl;
    std::cout << "Total weight of passengers: " << totalWeight << std::endl;

    *****************************************/

    

std::tuple < double, double > calculateSectionInfo(const std::string& sectionName)
{
    int numPassengers;
    double weight, totalWeight = 0.0, momentArm;
    std::vector < double >passengerWeights;

    std::cout << "Enter the number of passengers in " << sectionName << ": ";
    std::cin >> numPassengers;

    std::cout << "Enter the weight of each passenger:\n";
    for (int i = 0; i < numPassengers; ++i)
    {
        std::cout << "Passenger " << i + 1 << ": ";
        std::cin >> weight;
        passengerWeights.push_back(weight);	
        totalWeight += weight;
    }

    std::cout << "Enter the moment arm (in inches) for " << sectionName << ": ";
    std::cin >> momentArm;

    double sectionMoment = totalWeight * momentArm;
    return std::make_tuple(sectionMoment, totalWeight);	
}

int
main()

{
    //Airplane emopty weight intake
    double planeEmptyWeight;
    std::cout << "Enter the Airplane empty weight (pounds): ";
    std::cin >> planeEmptyWeight;

    double planeEmptyWeightMoment;
    std::cout << "Enter the Airplane empty-weight moment (pounds-inches): ";
    std::cin >> planeEmptyWeightMoment;

    //now we call our functions for the front and back seats
    double frontMoment, frontWeight, backMoment, backWeight;
    std::tie(frontMoment, frontWeight) = calculateSectionInfo("front seats");
    std::tie(backMoment, backWeight) = calculateSectionInfo("back seats");

    std::cout << "Front Section Moment: " << frontMoment << std::endl;
    std::cout << "Front Section Total Weight: " << frontWeight << std::endl;

    std::cout << "Back Section Moment: " << backMoment << std::endl;
    std::cout << "Back Section Total Weight: " << backWeight << std::endl;


    //Fuel
    double fuelGallons;
    std::cout << "Enter the number of gallons of usable fuel (gallons): ";
    std::cin >> fuelGallons;

    double fuelWeightPerGallon;
    std::cout << "Enter the usable fuel weight per gallon (pounds): ";
    std::cin >> fuelWeightPerGallon;

    double fuelWeight = fuelGallons * fuelWeightPerGallon;

    double fuelMomentArm;
    std::cout << "Enter the fuel tank moment arm: ";
    std::cin >> fuelMomentArm;

    double fuelMoment = fuelWeight * fuelMomentArm;

    //Baggage
    double baggageWeight;
    std::cout << "Enter the baggage weight (pounds): ";
    std::cin >> baggageWeight;

    double baggageMomentArm;
    std::cout << "Enter the baggage moment arm (inches): ";
    std::cin >> baggageMomentArm;

    double baggageMoment = baggageWeight * baggageMomentArm;


    //Gross Weight and CG Calculation
    double totalWeight = planeEmptyWeight + frontWeight + backWeight + fuelWeight + baggageWeight;
    double totalMoment = planeEmptyWeightMoment + frontMoment + backMoment + fuelMoment + baggageMoment;
    double cgLocation = totalMoment / totalWeight;

    //Declare airplane design limits
    double maxGrossWeight = 2950.0;
    double forwardCGLimit = 82.1;
    double aftCGLimit = 84.7;

    //Check Weigh and CG limits
    if (totalWeight >= maxGrossWeight || cgLocation < forwardCGLimit || cgLocation > aftCGLimit) {
        // Handle out-of-limits condition by adjusting fuel
        if (totalWeight > maxGrossWeight) {
            double fuelToRemove = (totalWeight - maxGrossWeight) / fuelWeightPerGallon;
            double totalRemovedFuel = 0.0;
            while (fuelToRemove >= 0.01) {
                fuelWeight -= 0.01;
                totalRemovedFuel += 0.01;
                totalWeight = planeEmptyWeight + frontWeight + backWeight + fuelWeight + baggageWeight;
                cgLocation = totalMoment / totalWeight;
                fuelToRemove -= 0.01;
            }

            std::cout << "Weight and CG are outside of design limits" << std::endl;
            std::cout << "Remove " << std::fixed << std::setprecision(2) << totalRemovedFuel << " lb of fuel" << std::endl;
            std::cout << "New Gross Weight: " << std::fixed << std::setprecision(2) << totalWeight << " lb" << std::endl;
            std::cout << "CG location: " << std::fixed << std::setprecision(2) << cgLocation << " inches" << std::endl;
        }
        else if (totalWeight < maxGrossWeight) {
            double fuelToAdd = (maxGrossWeight - totalWeight) / fuelWeightPerGallon;
            double totalAddedFuel = 0.0;
            while (fuelToAdd >= 0.01) {
                fuelWeight += 0.01;
                totalAddedFuel += 0.01;
                totalWeight = planeEmptyWeight + frontWeight + backWeight + fuelWeight + baggageWeight;
                cgLocation = totalMoment / totalWeight;
                fuelToAdd -= 0.01;
            }

            std::cout << "Weight and CG are outside of design limits" << std::endl;
            std::cout << "Add " << std::fixed << std::setprecision(2) << totalAddedFuel << " lb of fuel" << std::endl;
            std::cout << "New Gross Weight: " << std::fixed << std::setprecision(2) << totalWeight << " lb" << std::endl;
            std::cout << "CG location: " << std::fixed << std::setprecision(2) << cgLocation << " inches" << std::endl;
        }
    }

    return 0;

}