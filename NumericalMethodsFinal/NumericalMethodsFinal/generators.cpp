#include "generators.h"



// prompts user for inputs for all vehicle parameters based on the chosen simulation and returns a vehicle object with the input parameters.

Vehicle generateVehicle()
{
	//Variable declarations
	int loopCount;
	double mass, Cdrag, frontArea, diffRatio, wheelRadius, valueHold, maxRpm, driveForce, brakingForce;
	std::vector<double> gearRatios, revMap, torqueMap;
	std::string name;
	Vehicle returnVehicle;


	std::cout << std::endl << "--------------------------Enter data for simulation----------------------------" << std::endl;

	std::cout << std::endl << "Enter name of vehicle";
	name = util::getSanitizedInput<std::string>();

	std::cout << std::endl << "Enter mass of Vehicle (kg): ";
	mass = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter Cd: ";
	Cdrag =util::getSanitizedInput<double>();
	
	//Prompts user for a drive force unless simulation 4 was selected
	
	//std::cout << std::endl << "Enter drive force (N): ";
	//driveForce = util::getSanitizedInput<double>();
		
	std::cout << std::endl << "Enter front area (m^2): ";
	frontArea = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter wheel radius (m): ";
	wheelRadius = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter differential ratio: ";
	diffRatio = util::getSanitizedInput<double>();
	
	std::cout << std::endl << "Vehicle creation complete. Press any key to continue" << std::endl << std::endl;
	_getch();

	return Vehicle(mass, Cdrag, frontArea, diffRatio, wheelRadius, name);
}

engine generateEngine()
{
	int loopCount;
	double maxRpm, valueHold, efficiencyFactor;
	std::string engineName;
	std::vector<double> revMap, torqueMap;

	std::cout << std::endl << "Enter maximum RPM: ";
	maxRpm = util::getSanitizedInput<double>(0, LOWER_BOUND);

	std::cout << std::endl << "Enter engine name: ";
	engineName = util::getSanitizedInput<std::string>();

	if (util::yesNo("Efficiency factor?"))
	{
		std::cout << std::endl << "Enter engine efficiency factor: ";
		efficiencyFactor = util::getSanitizedInput<double>(0,1);
	}
	else efficiencyFactor = 1;

	return engine(revMap, torqueMap, engineName, efficiencyFactor);
}

Transmission generateTransmission()
{
	int numGears(0);
	double valueHold(0);
	bool hasEtas;
	std::string transName;
	std::vector<double> gearRatios, gearEtas;

	std::cout << "Enter number of gears: ";
	numGears = util::getSanitizedInput<int>(1,LOWER_BOUND);
	gearRatios.resize(numGears);
	gearEtas.assign(numGears, 1);

	hasEtas = util::yesNo("Does this gearbox have efficiencies?");

	std::cout << "Enter gearbox name: ";
	transName = util::getSanitizedInput<std::string>();

	//Prompts user to enter values for the transmission
	for (int i = 0; i < numGears; ++i)
	{
		std::cout << "Enter gear ratio for gear " << (i + 1) << ": ";

		if (i == 0)
			valueHold = util::getSanitizedInput<double>();
		else
			valueHold = util::getSanitizedInput<double>(0, gearRatios[i - 1]);

		gearRatios[i] = valueHold;

		if (hasEtas)
		{
			std::cout << "Enter efficiency for gear " << (i + 1) << ": ";
			valueHold = util::getSanitizedInput<double>(0,1);
			gearEtas[i] = valueHold;
		}
	}

	return Transmission(gearRatios, gearEtas, transName);
}


