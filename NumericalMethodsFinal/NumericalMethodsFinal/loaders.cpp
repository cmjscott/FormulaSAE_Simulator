#include "loaders.h"


namespace loaders
{
	std::vector<std::string> loadFile(std::string _fileName, componentType_e _componentType)
	{
		std::vector<std::string> data;
		std::ifstream inFile;
		std::string valueHold;

		std::string filePath = components.registeredComponents[_componentType] + "/" + _fileName + ".txt";

		inFile.open(filePath.c_str(), std::ios::in);

		//TODO: add error checking if the file is open, maybe throw some sort of error?
		inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		while (!inFile.eof())
		{
			std::getline(inFile, valueHold);
			data.push_back(valueHold);
			valueHold.clear();
		}

		return data;
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