#include "main.h"

//#ifdef _MSC_VER
//#define _CRT_SECURE_NO_WARNINGS
//#endif



const double MS_TO_MPH(2.2368);
componentSave components;

int main()
{
	std::vector<std::vector<double> > test1Data, test2Data, test3Data, test4Data, testData;
	std::vector<double> time, vel, gearRatios= { 2.785, 1.545, 1, .697 };
	std::string fileName;
	double rho, dt, timeToFullThrottle;
	int simulationFlag(99);				//get rid of default value later. for test purposes
	Vehicle simulationVehicle;

	//gearRatios.assign(ratioValues, ratioValues + sizeof(ratioValues) / sizeof(double));
	init();

	//prompts user to chose a simulation and then prompts them for each required input.
	do
	{
		//std::cout << "Which simulation would you like to run? (1, 2, 3, 4)" << std::endl;
		//simulationFlag = util::getSanitizedInput<int>(1,4);
		//std::cout << std::endl;
		
		if (simulationFlag == 99)
		{
			functionalityDemonstration();
			std::cout << "Demonstration simulations complete, press any key to quit";
			_getch();
			return 0;
		}
		

		std::cout << std::endl << "Enter time step (dt): ";
		dt = util::getSanitizedInput<double>();
		std::cout << std::endl;

		//creates a test vehicle based on simulation value entered
		simulationVehicle = generateVehicle();
		
		if (simulationFlag != 1)
		{
			std::cout << std::endl << "Enter air density rho (kg/m^3): ";
			rho = util::getSanitizedInput<double>();
			simulationVehicle.setRho(rho);
		}

		//based on the simulation value entered, runs the corrisponding simulation
		

		//promps user if they want to save the simulation data
		if (util::yesNo("Write results to file?"))
		{
			std::cout << std::endl << "Enter name of data file: ";
			fileName = util::getSanitizedInput<std::string>();

			savers::outputData(testData, fileName);
		}


	} while (util::yesNo("Run another simulation?")); //loop back through code and run another simulation.

	std::cout << "Simulations complete, press any key to quit";
	_getch();

	return 0;
}


std::vector<std::vector<double> > simulation4(Vehicle testVehicle, double _dt, double _timeToFullThrottle)
{
	/*
	NOTE: when I move simulation to its own object, in the simulation generator let them set certain parameters
	like time flags or acceleration/speed flags that lets them fine tune the simulation and when certain things activate
	and when things deactivate.
	ie: set how long it takes them to go from braking in a turn to full throttle, or if when accelerating from a throttle
	position of 0 to full, how long and how that's eased in. Stuff like that? not sure, would be cool.

	maybe look at APE and utilize some sort of test command queue that governs when each item activates and what it's triggers
	are. So the program would watch all the output items each itteration and then check the trigger parameters of the next
	simulation item against those values and would trigger them if they match. Don't know if a fifo stack would be the best
	or if just an array because several commands could be global or something?
	*/
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel, acceleration, torque, rpm, dataHolder;
	double throttle(0), zeroToSixtyTime(0);

	const double timeToFullThrottle = _timeToFullThrottle;

	//Sets initial values
	time.push_back(_dt);
	vel.push_back(0);
	acceleration.push_back(0);
	torque.push_back(0);
	rpm.push_back(0);
	//force.push_back(0);
	

	std::cout << "----------------------------------Simulation 4----------------------------------" << std::endl;

	do
	{
		dataHolder.clear();
		throttle = time.back()/timeToFullThrottle;
		dataHolder = testVehicle.simulateNextTimestep(vel.back(), _dt, throttle);
		
		time.push_back(time.back() + _dt);
		vel.push_back(dataHolder[0]);
		acceleration.push_back(dataHolder[1]);
		torque.push_back(dataHolder[2]);
		rpm.push_back(dataHolder[3]);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

	} while (time.back() < timeToFullThrottle);

	do
	{ 
		dataHolder.clear();
		dataHolder = testVehicle.simulateNextTimestep(vel.back(), _dt, throttle);

		time.push_back(time.back() + _dt);
		vel.push_back(dataHolder[0]);
		acceleration.push_back(dataHolder[1]);
		torque.push_back(dataHolder[2]);
		rpm.push_back(dataHolder[3]);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

	} while ((vel.back() - vel.rbegin()[1]) / _dt > .1); // keep calculating velocity until the acceleration is less than .01 (essentially at max velocity)

	std::cout << std::endl << "Your maximum velocity was " << vel.back() << " m/s  (" << vel.back() * MS_TO_MPH << " mph)" << std::endl;
	std::cout << "Time to reach maximum throttle position: " << timeToFullThrottle << " seconds." << std::endl;
	std::cout << "Time to reach maximum velocity: " << time.back() << " seconds." << std::endl;
	std::cout << "0 - 60 time: " << zeroToSixtyTime << " seconds." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	data.push_back(acceleration);
	data.push_back(torque);
	data.push_back(rpm);
	return data;
}

void functionalityDemonstration()
{
	/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for default simulation
	Cd = .32
	A = 23.4 ft^2 = 2.1739 m^2
	mass = 3715 lbs = 1685.1 kg
	Drive force ~ 1500 N
	Braking force ~ 7700 N
	Gear Ratios:
	1st 2.785
	2nd 1.545
	3rd 1.000
	4th 0.697
	Rev 2.272
	Diff 4.11

	Tires: 225/60R16 98H SL
	wheelRadius = 0.33782 m
	
	RPM =    { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
	torque = { 240 , 250 , 260 , 270 , 280 , 290 , 300 , 305 , 310 , 305 , 295 , 285 , 280 , 270 , 260  };
	*/

	std::vector<std::vector<double> > test4Data;
	std::vector<std::string> gearboxArray;
	std::vector<double> revMap = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
	std::vector<double> torqueMap = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };
	std::vector<double> gearRatios = { 2.785, 1.545, 1, .697 };
	double rho(1.2041), dt(.001), mass(1685.1), Cdrag(.32), driveForce(1700), frontArea(2.1739), brakingForce(7700), diffRatio(4.11), wheelRadius(.33782);
	std::string name = "james";
	//create test objects from hard coded data above
	//Vehicle testVehicle(mass, Cdrag, frontArea, diffRatio, wheelRadius, name, rho);
	//engine testEngine = engine(revMap, torqueMap, "test_engine");

	// create test objects using the generators
	//Transmission testTransmission = generateTransmission();
	//engine testEngine = generateEngine();
	
	Vehicle testVehicle = loaders::loadVehicle("test_vehicle_save.txt");
	engine testEngine = loaders::loadEngine("test_engine_save.txt");
	Transmission testTransmission;

	testVehicle.attachEngine(testEngine);

	/*
	Transmission testTransmission = loaders::loadTransmission("test_transmission_save");
	testTransmission = generateTransmission();
	savers::saveComponent(testTransmission, "test_transmission_save2", COMPONENT_TRANSMISSION);
	testTransmission = generateTransmission();
	savers::saveComponent(testTransmission, "test_transmission_save3", COMPONENT_TRANSMISSION);
	testTransmission = generateTransmission();
	savers::saveComponent(testTransmission, "test_transmission_save4", COMPONENT_TRANSMISSION);
	*/

	gearboxArray = listDir(COMPONENT_TRANSMISSION);

	for (const auto& i : gearboxArray)
	{
		testTransmission = loaders::loadTransmission(i);
		testVehicle.attachTransmission(testTransmission);
		test4Data = simulation4(testVehicle, dt);
		savers::outputData(test4Data, testTransmission.name);
	}


	savers::saveComponent(testEngine, "test_engine_save", COMPONENT_ENGINE);
	savers::saveComponent(testVehicle, "test_vehicle_save", COMPONENT_VEHICLE);
	
	//Run simulations
	//test4Data = simulation4(testVehicle, dt);
	
	//save results
	//savers::outputData(test4Data, "test_output_data");

}


void init()
{
	// make sure all directories are created and ready here
	std::string outputFolder;

	components.registerComponent(COMPONENT_ENGINE, "../Engines");
	components.registerComponent(COMPONENT_TRANSMISSION, "../Transmissions");
	components.registerComponent(COMPONENT_VEHICLE, "../Vehicles");
	components.registerComponent(COMPONENT_RESULTS, "../Results");
	
	for (auto i : components.registeredComponents)
	{
		outputFolder = i.second;
		if (CreateDirectory(outputFolder.c_str(), NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			std::cout << outputFolder <<  ": Folder created or exists" << std::endl;
		}
		else
		{
			std::cout << "Folder not created" << std::endl;
		}
	}

	//std::string(OutputFolder + CopiedFile).c_str();
	
}


//Depreciated
/*
std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	double zeroToSixtyTime(0);
	
	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	std::cout << "-------------------------------Simulation 1 and 2-------------------------------" << std::endl;

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt));
		time.push_back(time.back() + _dt);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

	} while ((vel.back() - vel.rbegin()[1])/_dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	std::cout << "Your maximum velocity was " << vel.back() << " m/s  (" << vel.back() * MS_TO_MPH << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;
	std::cout << "0 - 60 time: " << zeroToSixtyTime << " seconds." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}

std::vector<std::vector<double> > simulation3(Vehicle testVehicle, double _dt)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	double maxSpeed, timeMaxSpeed, zeroToSixtyTime(0);


	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	std::cout << "----------------------------------Simulation 3----------------------------------" << std::endl;

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt));
		time.push_back(time.back() + _dt);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

	} while ((vel.back() - vel.rbegin()[1]) / _dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	maxSpeed = vel.back();
	timeMaxSpeed = time.back();
	
	do
	{
		vel.push_back(testVehicle.brake(vel.back(), _dt));
		time.push_back(time.back() + _dt);
	} while (vel.back() > 0);

	if (vel.back() < 0)
		vel.back() = 0;

	std::cout << "Your maximum velocity was " << maxSpeed << " m/s  (" << maxSpeed * MS_TO_MPH << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;
	std::cout << "Time to come to a complete stop: " << time.back() - timeMaxSpeed << "seconds." << std::endl;
	std::cout << "0 - 60 time: " << zeroToSixtyTime << " seconds." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}
*/