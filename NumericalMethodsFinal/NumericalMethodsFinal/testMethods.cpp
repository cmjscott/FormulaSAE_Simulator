#include "main.h"
#include "testMethods.h"


void test()
{
	engine testEngine = testCreateEngine();
	std::cout << testEngine;

	Transmission testTransmission = testCreateTransmission();
	std::cout << testTransmission;

	Vehicle testVehicle = testCreateVehicle();
	std::cout << testVehicle;

	testVehicle.attachEngine(testEngine);
	testVehicle.attachTransmission(testTransmission);

	testPrintVector();

	std::cout << "Test Complete." << std::endl;
}

void testPrintVector()
{
	std::cout << listDir(COMPONENT_TRANSMISSION) << std::endl;
}

engine testCreateEngine()
{
	std::vector<double> testRPM = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
	std::vector<double> testTorque = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };
	std::string name = "TEST_ENGINE";
	
	engine testEngine = engine(testRPM, testTorque, name);
	savers::saveComponent(testEngine, "test_engine", COMPONENT_ENGINE);
	return loaders::loadEngine("test_engine.txt");
}

Transmission testCreateTransmission()
{
	std::vector<double> testGearRatios = { 2.785, 1.545, 1, .697 };
	std::string name = "TEST_TRANSMISSION";

	Transmission testTransmission = Transmission(testGearRatios, name);
	savers::saveComponent(testTransmission, "test_transmission", COMPONENT_TRANSMISSION);
	return loaders::loadTransmission("test_transmission.txt");
}

Vehicle testCreateVehicle()
{
	double  mass(1685.1), Cdrag(.32), frontArea(2.1739), diffRatio(4.11), wheelRadius(.33782), rho(1.2041);
	std::string name = "TEST_VEHICLE";

	Vehicle testVehicle = Vehicle(mass, Cdrag, frontArea, diffRatio, wheelRadius, name, rho);
	savers::saveComponent(testVehicle, "test_vehicle", COMPONENT_VEHICLE);
	return loaders::loadVehicle("test_vehicle.txt");
}
