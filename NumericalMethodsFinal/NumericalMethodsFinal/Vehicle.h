#pragma once

#include <cmath>
#include <iostream>


/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
Cd = .32
A = 23.4 ft^2 = 2.1739 m^2
mass = 3715 lbs = 1685.1 kg
*/


class Vehicle
{
public:

	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag, double _fDrive);
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea);
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea, double _fBrake);
	Vehicle::Vehicle(double _mass, double _Cdrag, double _frontalArea,
					 double _gearRatio, double _diffRatio, double wheelRadius);
	//Vehicle(double _mass, double _Cdrag, double _frontalArea, double _gearRatio, double _diffRatio, double _wheelRadius);


	//member functions
	double velocity(double _currVelocity, double dt, double *rho, double throttle = -1);
	double brake(double _currVelocity, double dt, double *rho);
	~Vehicle();
	

private:

	//Member private functions
	double accel(double *rho, double throttle = -1);
	double deccel(double *rho);
	double fTorque(double throttle);
	double Torque(double throttle);
	double RPM(double throttle);
	double fDrag(double *rho);    //returns the drag forces ascociated with air resistance
	double Frr();                 //returns the resistance ascociated with rolling
	



	//Member private properties
	double mass;
	double Cdrag;
	double Crr;
	double currVelocity;
	double frontArea;
	double fDrive;
	double fBrake;

	double gearRatio;
	double diffRatio;
	double wheelRadius;
	bool torqueDrive;
	static double transEff;

};

