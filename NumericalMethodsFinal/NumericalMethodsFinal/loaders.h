#pragma once

#ifndef _INC_LOADERS
#define _INC_LOADERS

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <exception>
#include "Transmission.h"
#include "engine.h"
#include "Vehicle.h"
#include "Structs.h"

extern componentSave components;

namespace loaders
{
	std::vector<std::string> loadFile(std::string _fileName, componentType_e _componentType);
	Vehicle loadVehicle(std::string _fileName);
	Transmission loadTransmission(std::string _fileName);
	engine loadEngine(std::string _fileName);
	std::vector<double> extractDoubles(std::string line);

} // namespace loaders


#endif