#include "Physics.h"
#include <iostream>  // for CIN and COUT
using namespace std;
#include <cmath>
#include <iomanip>

#define WEIGHT   46.7   // Weight in KG

Physics::Physics() {
    angle = 0;
    x = 14000;
    y = 4000;
    velocity = 827;
    dx = 0;
    dy = 0;
    dragCoefficient = 0;
    mach = 0;
    drag = 0;
    airDensity = 0;
    surfaceArea = 3.14159 * (0.077445 * 0.077445);
    gravity = -9.8;

    Position defaultPos(14000,14000);

    for (int i = 0; i < 20; i++) {
        history[i] = defaultPos;
        defaultPos.setMetersX(defaultPos.getMetersX() + 40);
    }
    
};

/***************************************************
    * COMPUTE DISTANCE 
    * Apply inertia to compute a new position using the distance equation.
    * The equation is:
    *     s = s + v t + 1/2 a t^2
    * INPUT
    *     s : original position, in meters
    *     v : velocity, in meters/second
    *     a : acceleration, in meters/second^2
    *     t : time, in seconds
    * OUTPUT
    *     s : new position, in meters
    **************************************************/

double Physics::computeDistance(double s, double v, double a, double t) {
    return s + v * t + 0.5 * a * (t * t);
}
/**************************************************
    * COMPUTE ACCELERATION
    * Find the acceleration given a thrust and mass.
    * This will be done using Newton's second law of motion:
    *     f = m * a
    * INPUT
    *     f : force, in Newtons (kg * m / s^2)
    *     m : mass, in kilograms
    * OUTPUT
    *     a : acceleration, in meters/second^2
    ***************************************************/

double Physics::computeAcceleration(double f, double m)
{
    if (m > 0) {
        return f / m;
    }
    return 0;
}

/***********************************************
    * COMPUTE VELOCITY
    * Starting with a given velocity, find the new
    * velocity once acceleration is applied. This is
    * called the Kinematics equation. The
    * equation is:
    *     v = v + a t
    * INPUT
    *     v : velocity, in meters/second
    *     a : acceleration, in meters/second^2
    *     t : time, in seconds
    * OUTPUT
    *     v : new velocity, in meters/second
    ***********************************************/

double Physics::computeVelocity(double v, double a, double t) {
    return v + a * t;
}

/***********************************************
    * COMPUTE VERTICAL COMPONENT
    * Find the vertical component of a velocity or acceleration.
    * The equation is:
    *     cos(a) = y / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     y : the vertical component of the total
    ***********************************************/

double Physics::findVerticalComponent(double a, double total) {
    return cos(a) * total;
}
/***********************************************
    * COMPUTE HORIZONTAL COMPONENT
    * Find the horizontal component of a velocity or acceleration.
    * The equation is:
    *     sin(a) = x / total
    * This can be expressed graphically:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    |a/
    *    |/
    * INPUT
    *     a : angle, in radians
    *     total : total velocity or acceleration
    * OUTPUT
    *     x : the vertical component of the total
    ***********************************************/

double Physics::findHorizontalComponent(double a, double total) {
    return sin(a) * total;
}
/************************************************
    * COMPUTE TOTAL COMPONENT
    * Given the horizontal and vertical components of
    * something (velocity or acceleration), determine
    * the total component. To do this, use the Pythagorean Theorem:
    *    x^2 + y^2 = t^2
    * where:
    *      x
    *    +-----
    *    |   /
    *  y |  / total
    *    | /
    *    |/
    * INPUT
    *    x : horizontal component
    *    y : vertical component
    * OUTPUT
    *    total : total component
    ***********************************************/

double Physics::findTotalComponent(double dx, double dy) {
    double total = (pow(dx, 2) + pow(dy, 2));
    return sqrt(total);
}

/*************************************************
    * RADIANS FROM DEGEES
    * Convert degrees to radians:
    *     radians / 2pi = degrees / 360
    * INPUT
    *     d : degrees from 0 to 360
    * OUTPUT
    *     r : radians from 0 to 2pi
    **************************************************/

double Physics::radiansFromDegrees(double d) {
    return (d / 360) * 2 * 3.14159265;
}

/*******************************************
* Drag Force Equation 
* Find drag 
*******************************************/
double Physics::findDrag(double dragCoefficient, double density, double velocity, double area) {
    return .5 * (dragCoefficient * density * (velocity * velocity) * area);
}

/*******************************************
* Area of a circle 
*******************************************/
double Physics::findAreaOfCircle(double radius) {
    if (radius > 0) {
        return 3.1415 * (radius * radius);
    }
    return 0;
}

/*******************************************
* Linear interpolation equation 
* (r - r0) / (d - d0) = (r1 - r0) / (d1 - d0)
* where d0,r0 are the coordinates of one point 
* and d1,r1 are the coordinates of a second point 
* and d,r are the coordinates of a point in the middle 
*******************************************/
double Physics::linearInterpolation(double d0, double r0, double d1, double r1, double r) {
    if (r1 - r0 != 0) {
        return d0 + (r - r0) * ((d1 - d0) / (r1 - r0));
    }
    return 0;
}

/*******************************************
* Find gravity from the altitude 
* using linear interpolation 
*******************************************/
double Physics::findGravity(double altitude1) {
    double altitude[14] = {1,      1000,    2000,   3000,  4000,   5000,   6000,   7000,   8000,   9000,  10000,   15000,  20000,  25000};
    double gravity[14] = {-9.807, -9.804, -9.801, -9.797, -9.794, -9.791, -9.788, -9.785, -9.782, -9.779, -9.776, -9.761, -9.745, -9.730 };

    for (int i = 1; i < 14; i++) {
        if (altitude1 <= 0.01) {
            return -9.807;
        }
        if (altitude[i] > altitude1) {
            return linearInterpolation(gravity[i - 1], altitude[i - 1], gravity[i], altitude[i], altitude1);
        }
    }

    return gravity[13];
}

/*******************************************
* Find speed of sound from the altitude
* using linear interpolation
*******************************************/
double Physics::findSpeed(double altitude1) { // speed of sound 
    double altitude[16] = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000, 25000, 30000, 40000 };// in m
    double speed[16] =   {340, 336,   332,  328,  324,  320,  316,  312,  308,  303,  299,    295,   295,   295,   305, 324};//in m/s
	
    for (int i = 1; i < 16; i++) {
		if (altitude1 <= 0.01) {
			return 340;
		}
		if (altitude[i] > altitude1) {
			return linearInterpolation(speed[i - 1], altitude[i - 1], speed[i], altitude[i], altitude1);
		}
	}

	return speed[15];
}

/*******************************************
* Find drag coefficient from Mach / speed of sound 
* using linear interpolation
*******************************************/
double Physics::findDragCoefficient(double speed1) {
    double mach[16] =        {0.300,   0.500,  0.700,  0.890,  0.920,  0.960,  0.980,  1.000,  1.020,  1.060,  1.240,  1.530,  1.990,  2.870,  2.890,  5.000};
    double coefficient[16] = { 0.1629, 0.1659, 0.2031, 0.2597, 0.3010, 0.3287, 0.4002, 0.4258, 0.4335, 0.4483, 0.4064, 0.3663, 0.2897, 0.2297, 0.2306, 0.2656 };
	
    for (int i = 1; i < 16; i++) {
		if (speed1 <= 0.3) {
			return 0.1629;
		}
		if (mach[i] > speed1) {
			return linearInterpolation(coefficient[i - 1], mach[i - 1], coefficient[i], mach[i], speed1);
		}
	}

	return coefficient[15];

    return 0;
}

/*******************************************
* Find air density from the altitude 
* using linear interpolation
*******************************************/
double Physics::findDensity(double altitude1) {
    double altitude[20] = {       0,       1000,      2000,     3000,      4000,      5000,      6000,      7000,      8000,     9000,      10000,      15000,     20000,     25000,     30000,     40000,     50000,     60000,     70000, 80000};
    double density[20] = { 1.2250000, 1.1120000, 1.0070000, 0.9093000, 0.8194000, 0.7364000, 0.6601000, 0.5900000, 0.5258000, 0.4671000, 0.4135000, 0.1948000, 0.0889100, 0.0400800, 0.0184100, 0.0039960, 0.0010270, 0.0003097, 0.0000828, 0.0000185 };

	for (int i = 1; i < 20; i++) {
		if (altitude1 <= 0.0) {
			return 1.2250000;
		}
		if (altitude[i] > altitude1) {
			return linearInterpolation(density[i - 1], altitude[i - 1], density[i], altitude[i], altitude1);
		}
	}
    
    return density[19];
}

/*******************************************
* Find angle from components 
* Equation: a = atan2(dx, dy)
* where a is the angle/direction of travel 
* dx is the horizontal component of speed (m/s)
* dy is the vertical component of speed (m/s)
*******************************************/
double Physics::findAngle(float dx, float dy)
{
    return atan2(dx, dy);
}

/*******************************************
* Return last 20 positions of the bullet
*******************************************/
Position* Physics::getHistory()
{
    return history;
}

/*******************************************
* removes last position of history and adds the new position to the front
*******************************************/
void Physics::addHistory(Position position) {
    for (int i = 19; i >= 1; i--) {
        history[i] = history[i - 1];
    }
    history[0] = position;
}

/*******************************************
* shoots the bullet
* sets bullet velocity, angle, and position
*******************************************/
void Physics::shootBullet(double angle, Position pHowtzer) {
    x = pHowtzer.getMetersX();
    y = pHowtzer.getMetersY();
    velocity = 827;
    this->angle = angle;
    dx = findHorizontalComponent(this->angle, velocity);
    dy = findVerticalComponent(this->angle, velocity);

    for (int i = 0; i < 20; i++) {
        addHistory(Position(x, y));
    }
}

/*******************************************
* puts the whole class together to find the new position of the bullet
*******************************************/
void Physics::compute() {

    x = history[0].getMetersX();
    y = history[0].getMetersY();
    gravity = findGravity(y);
    airDensity = (findDensity(y));
    angle = findAngle(dx, dy);
    velocity = findTotalComponent(dx, dy);
    mach = velocity / findSpeed(y);

    dragCoefficient = findDragCoefficient(mach);


    drag = findDrag(dragCoefficient, airDensity, velocity, surfaceArea);
    float acceleration = computeAcceleration(drag, WEIGHT);
    float ddx = acceleration * -sin(angle);
    float ddy = acceleration * -cos(angle) + gravity;

    // computeAcceleration parameters are (force, then mass) 
    dy = computeVelocity(dy, ddy, .5);
    dx = computeVelocity(dx, ddx, .5);

    x = computeDistance(x, dx, ddx, .5);
    y = computeDistance(y, dy, ddy, .5);

    

    Position bulletPos(x, y);
    addHistory(bulletPos);
    if (y <= 0) {
        x = linearInterpolation(x, y, x + dx / 100, y + dy / 100, 0);
        y = 0;
    }

}
