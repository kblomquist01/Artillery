#pragma once
class Physics
{
public:
	double computeDistance(double s, double v, double a, double t);
	double computeAcceleration(double f, double m);
	double computeVelocity(double v, double a, double t);
	double findVerticalComponent(double a, double total);
	double findHorizontalComponent(double a, double total);
	double findTotalComponent(double dx, double dy);
	double radiansFromDegrees(double d);
	void changeVelocity(double aRadians, bool thrusting);
	double getTotalVelocity();
	double getDX();
	double getDY();
private:
	#define WEIGHT   46.7   // Weight in KG
	#define GRAVITY  0.0 // start at 0 for testing  -9.8   // Vertical acceleration due to gravity, in m/s^2
	double x;
	double y;
	float dx;
	float dy;
	double ddx;
	double ddy;
	double acceleration;
	double drag;
	int angle;
	double distance; // in meters 
	double hangTime; // in seconds 


};

