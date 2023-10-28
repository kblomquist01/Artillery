//#include "Physics.h"
#include <iostream>  // for CIN and COUT
using namespace std;
#include <cmath>

#define WEIGHT   46.7   // Weight in KG

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

double computeDistance(double s, double v, double a, double t) {
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

//double computeAcceleration(double f, double m)
//{
//    double a = f / m;
//    return a;
//}

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

double computeVelocity(double v, double a, double t) {
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

double findVerticalComponent(double a, double total) {    
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

double findHorizontalComponent(double a, double total) {
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

//double findTotalComponent(double dx, double dy) {
//    double total = (pow(dx, 2) + pow(dy, 2));
//    return sqrt(total);
//}

/*************************************************
    * RADIANS FROM DEGEES
    * Convert degrees to radians:
    *     radians / 2pi = degrees / 360
    * INPUT
    *     d : degrees from 0 to 360
    * OUTPUT
    *     r : radians from 0 to 2pi
    **************************************************/

double radiansFromDegrees(double d) {
    return (d / 360) * 2 * 3.14159265;
}

//void changeVelocity(double aRadians, bool thrusting)
//{
//    double time = .1;
//
////    double drag = findDrag(dragCoefficient, density, velocity, area);
//
//    double accelerationThrust = computeAcceleration(drag, WEIGHT);  // Acceleration due to thrust 
//    double ddxThrust = findHorizontalComponent(aRadians, drag);           // Horizontal acceleration due to thrust
//    double ddyThrust = findVerticalComponent(aRadians, drag);           // Vertical acceleration due to thrust
//    double ddx = computeAcceleration(ddxThrust, WEIGHT);       //-2.105;          // Total horizontal acceleration
//    double ddy = computeAcceleration(ddyThrust, WEIGHT) + GRAVITY;  //0.48;               // Total vertical acceleration
//
//    dx = computeVelocity(dx, ddx, time);
//    dy = computeVelocity(dy, ddy, time);
//}

/*******************************************
* RETURN
* total velcocity
*******************************************/
//double getTotalVelocity() {
//    return findTotalComponent(dx, dy);
//}

/*******************************************
* RETURN
* dx : X velocity
*******************************************/
//double getDX() {
//    return dx;
//}

/*******************************************
* RETURN
* dy : Y velocity
*******************************************/
//double getDY() {
//    return dy;
//}

/*******************************************
* Drag Force Equation 
* Find drag 
*******************************************/
double findDrag(double dragCoefficient, double density, double velocity, double area) {
    return .5 * (dragCoefficient * density * (velocity * velocity) * area);
}

/*******************************************
* Area of a circle 
*******************************************/
double findAreaOfCircle(double radius) {
    return 3.1415 * (radius * radius);
}

/*******************************************
* Newton's second law of motion 
* Return force 
*******************************************/
double lawOfMotion(double mass, double acceleration) {
    return mass * acceleration;
}
/*******************************************
* Linear interpolation equation 
* (r - r0) / (d - d0) = (r1 - r0) / (d1 - d0)
* where d0,r0 are the coordinates of one point 
* and d1,r1 are the coordinates of a second point 
* and d,r are the coordinates of a point in the middle 
* that you are trying to find 
* Returns 
*******************************************/
double linearInterpolation(double d0, double r0, double d1, double r1, double r) {
    return d0 + (r - r0) * ((d1 - d0) / (r1 - r0));
}

double findGravity() {
//    double info[6] = [1,2,3,4,5,6];
    return 0;
}

/*******************************************
* Find angle from components 
* Equation: a = atan2(dx, dy)
* where a is the angle/direction of travel 
* dx is the horizontal component of speed (m/s)
* dy is the vertical component of speed (m/s)
*******************************************/
//double findAngle()
//{
//    return atan2(dx, dy);
//}


int main() {
    double angle = radiansFromDegrees(75);
    double x = 0;
    double y = .01;
    float velocity = 827;
    float dx = findHorizontalComponent(angle, velocity);
    float dy = findVerticalComponent(angle, velocity);
    double ddx = 0;
    double ddy = 0;
    double acceleration = 0;
    double drag = 0;
    double gravity = -9.8;

    double distance = 0; // in meters 
    double hangTime = 0;
    
    while(y > 0) {

        dy = computeVelocity(dy, gravity, .01);
        x = computeDistance(x, dx, 0, .01);
        y = computeDistance(y, dy, gravity, .01);

        hangTime += .01;
        
        
    }

    cout << "distance: " << x << "m Altitude: " << y << "m Hang time: " << hangTime << "s";


    return 0;
}
