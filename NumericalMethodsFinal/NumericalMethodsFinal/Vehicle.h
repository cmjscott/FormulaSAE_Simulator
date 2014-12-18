#pragma once

#ifndef _INC_VEHICLE
#define _INC_VEHICLE

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
//#include "prettyprint.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "engine.h"

class Vehicle
{
public:
	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag, double _fDrive);															//constructor for simulation 1
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea);										//constructor for simulation 2
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea, double _fBrake);						//constructor for simulation 3
	Vehicle(double _mass, double _Cdrag, double _frontalArea,std::vector<double> _gearRatio,						// constructor for simulation 4
		double _diffRatios, double wheelRadius, double _rho = 1);
	

	//public member functions
	double velocity(double _currVelocity, double dt, double throttle = -1);
	double brake(double _currVelocity, double dt);
	double engineDriveForce(double throttle);
	double getRPM();
	void setRho(double _rho);
	void attachEngine(engine* _engine);
	~Vehicle();

	//public friend functions
	friend std::ostream& operator << (std::ostream& out, const Vehicle& obj);
	
	//public member variables
	int simulationFlag;

private:

	//Member private functions
	double accel(double throttle = -1);
	double deccel();
	void shift();				  //shifts if rpm range is ideal
	double fDrag();    //returns the drag forces ascociated with air resistance
	double Frr();                 //returns the resistance ascociated with rolling

	//depreciated
	//int findPeakTorque();
	
	

	//Member private properties
	double mass;
	double Cdrag;
	double Crr;
	double currVelocity;
	double frontArea;
	double fDrive;
	double fBrake;
	double rho;
	double diffRatio;
	double wheelRadius;
	int currGear;
	double transEff;

	std::vector<double> gearRatios;
	std::vector<std::vector<double> > stateData;

	engine* attachedEngine;

	//depreciated
	//std::vector<double> revMap;
	//std::vector<double> torqueMap;
	//int peakTorqueIndex;
};

#endif
