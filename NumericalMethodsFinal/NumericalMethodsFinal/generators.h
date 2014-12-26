#pragma once

#ifndef _INC_GENERATORS
#define _INC_GENERATORS

#include <vector>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include "Vehicle.h"
#include "engine.h"
#include "Transmission.h"
#include "utilityFunctions.h"



Vehicle generateVehicle(int simulationFlag);
engine generateEngine();
Transmission generateTransmission();



#endif