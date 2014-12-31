#include "loaders.h"


namespace loaders
{
	std::vector<std::string> loadFile(std::string _fileName, componentType_e _componentType)
	{
		std::vector<std::string> data;
		std::string valueHold;

		std::string filePath = globalAccess::filePaths.registeredComponents[_componentType] + "/" + _fileName;

		std::ifstream inFile(filePath.c_str(), std::ios::in);

		if (!inFile.good())
			throw std::ios_base::failure("Error, file not found.");

		//TODO: add error checking if the file is open, maybe throw some sort of error?

		inFile.ignore(255, '\n');		//ignores the first line of the file, which is the component type tag. I might use this later.

		while (!inFile.eof())
		{
			std::getline(inFile, valueHold);
			data.push_back(valueHold);
			valueHold.clear();
		}

		return data;
	}

	Vehicle loadVehicle(std::string _fileName)
	{
		std::vector<std::string> data;
		Vehicle loadedVehicle;
		std::string loadedName;
		double mass, Cdrag, frontalArea, diffRatio, wheelRadius, rho;

		data = loadFile(_fileName, COMPONENT_VEHICLE);
		loadedName = data[0];
		mass = extractDoubles(data[1])[0];
		Cdrag = extractDoubles(data[2])[0];
		frontalArea = extractDoubles(data[3])[0];
		diffRatio = extractDoubles(data[5])[0];
		wheelRadius = extractDoubles(data[6])[0];
		rho = extractDoubles(data[8])[0];

		loadedVehicle = Vehicle(mass, Cdrag, frontalArea, diffRatio, wheelRadius, loadedName, rho);

		return loadedVehicle;
	}

	Transmission loadTransmission(std::string _fileName)
	{
		std::vector<std::string> data;
		Transmission loadedTransmission;
		std::string loadedName;
		std::vector<double> gearRatios, gearEtas;
		
		data = loadFile(_fileName, COMPONENT_TRANSMISSION);
		loadedName = data[0];
		gearRatios = extractDoubles(data[1]);
		gearEtas = extractDoubles(data[2]);
		loadedTransmission = Transmission(gearRatios, gearEtas, loadedName);

		return loadedTransmission;
	}

	engine loadEngine(std::string _fileName)
	{
		std::vector<std::string> data;
		engine loadedEngine;
		std::string loadedName;
		std::vector<double> rpms, torques;
		double efficiency;

		data = loadFile(_fileName, COMPONENT_ENGINE);
		loadedName = data[0];
		rpms = extractDoubles(data[1]);
		torques = extractDoubles(data[2]);
		efficiency = extractDoubles(data[3])[0];
		loadedEngine = engine(rpms, torques, loadedName, efficiency);

		return loadedEngine;
	}

	std::vector<double> extractDoubles(std::string line)
	{

		double valueHold;
		std::stringstream dataStream;
		std::vector<double> extractedData;

		dataStream.str(line);
		dataStream.ignore(255,':');

		while (!dataStream.eof())
		{
			dataStream >> valueHold;

			if (dataStream.fail())
			{
				dataStream.ignore();
				dataStream.clear();
			}
			else
				dataStream.ignore();

			extractedData.push_back(valueHold);
			if (dataStream.rdbuf()->in_avail() == 0)
				dataStream.setstate(std::ios::eofbit);
		}
		return extractedData;
	}
}