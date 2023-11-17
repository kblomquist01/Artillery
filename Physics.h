#pragma once
#include "position.h"

class Physics
{
	friend class TestPhysics;
public:
	double computeDistance(double s, double v, double a, double t);
	double computeAcceleration(double f, double m);
	double computeVelocity(double v, double a, double t);
	double findVerticalComponent(double a, double total);
	double findHorizontalComponent(double a, double total);
	double findTotalComponent(double dx, double dy);
	double radiansFromDegrees(double d);
	//void changeVelocity(double aRadians, bool thrusting);
	//double getTotalVelocity();
	//double getDX();
	//double getDY();
	double findDrag(double dragCoefficient, double density, double velocity, double area);
	double findAreaOfCircle(double radius);
	double linearInterpolation(double d0, double r0, double d1, double r1, double r);
	double findGravity(double altitude1);
	double findSpeed(double altitude1);
	double findDragCoefficient(double speed1);
	double findDensity(double altitude1);
	double findAngle(float dx, float dy);
	Position* getHistory();
	void addHistory(Position position);
	
private:
	#define WEIGHT   46.7   // Weight in KG
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
	Position history[3];
};

