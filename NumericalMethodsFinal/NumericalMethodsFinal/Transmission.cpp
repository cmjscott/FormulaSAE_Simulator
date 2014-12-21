#include "Transmission.h"


Transmission::Transmission(){}

Transmission::Transmission(std::vector<double> _gearRatios)
{
	gearRatios = _gearRatios;
	gearEtas.assign(gearRatios.size(),1);
	gearRatios.shrink_to_fit();

	shiftTime = 0;
	shifting = false;
	currentGearIndex = 0;
	minGear = true;
	maxGear = false;
}

Transmission::Transmission(std::vector<double> _gearRatios, std::vector<double> _gearEtas)
{
	gearRatios = _gearRatios;
	gearEtas = _gearEtas;
	gearRatios.shrink_to_fit();

	shiftTime = 0;
	shifting = false;
	currentGearIndex = 0;
	minGear = true;
	maxGear = false;
}

Transmission::~Transmission(){}


void Transmission::upshift()
{
	if (currentGearIndex + 1 < gearRatios.size())
		currentGearIndex++;

	if (currentGearIndex + 1 == gearRatios.size())
		maxGear = true;
	else
		maxGear = false;
}

void Transmission::downshift()
{
	if (currentGearIndex > 0)
		currentGearIndex--;

	if (currentGearIndex == 0)
		minGear = true;
	else
		minGear = false;
}

double Transmission::getRatio() { return gearRatios[currentGearIndex]; }

double Transmission::getNextRatio()
{
	if (maxGear)
		return gearRatios[currentGearIndex];
	else 
		return gearRatios[currentGearIndex + 1];
}

double Transmission::getPreviousRatio()
{
	if (minGear)
		return gearRatios[currentGearIndex];
	else
		return gearRatios[currentGearIndex - 1];
}

std::ostream& operator << (std::ostream& out, const Transmission& obj)
{
	out << "Gear Ratios:";
	for (auto i : obj.gearRatios)
		out << i << ",";
	out << std::endl;

	out << "Gear Etas:";
	for (auto i : obj.gearEtas)
		out << i << ",";
	out << std::endl;

	return out;
}