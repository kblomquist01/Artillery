#pragma once

#include "physics.h"
#include <cassert>
using namespace std;

/*******************************
 * Test Physics class with unit tests
 ********************************/


/* Instructions from the assignment 
Each unit test should have four parts: Setup, Exercise, Verify, and Teardown. 
Note that a unit test for a function only needs two parts: Exercise and Verify.
Most functions will need at least 2 or 3 unit tests to get sufficient coverage, 
and most classes need to have every non-trivial method tested. 
This means that a few dozen unit tests will need to be created.
*/


class TestPhysics
{
public:
	void run() {
		testComputeDistance();
		testComputeAcceleration();
		testComputeVelocity();
		testFindVerticalComponent();
		testFindHorizontalComponent();
		testFindTotalComponent();
		testRadiansFromDegrees();
		testFindDrag();
		testFindAreaOfCircle();
		testLinearInterpolation();
		testFindGravity();
		testFindSpeed();
		testFindDragCoefficient();
		testFindDensity();
		testFindAngle();
		testGetHistory();
	}
private:
	void testComputeDistance() {
		Physics phy;

		//zero inputs
		assert(phy.computeDistance(0,0,0,0) == 0.0);
		//start postion test
		assert(phy.computeDistance(1.0, 0, 0, 0) == 1.0);
		//time only
		assert(phy.computeDistance(0, 0, 0, 1.0) == 0.0);
		//velocity no time
		assert(phy.computeDistance(0, 1.0, 0, 0) == 0.0);
		//velocity time
		assert(phy.computeDistance(0, 1.0, 0, 1.0) == 1.0);
		//velocity
		assert(phy.computeDistance(0, 2.0, 0, 1.0) == 2.0);
		//time to velocity
		assert(phy.computeDistance(0, 1.0, 0, 2.0) == 2.0);
		//acceleration no time
		assert(phy.computeDistance(0, 0, 1.0, 0) == 0);
		//acceleration time
		assert(phy.computeDistance(0, 0, 1.0, 1.0) == 0.5);
		//acceleration
		assert(phy.computeDistance(0, 0, 2.0, 1.0) == 1.0);
		//time to acceleration
		assert(phy.computeDistance(0, 0, 1.0, 2.0) == 2.0);
		//negative velocity
		assert(phy.computeDistance(0, -1.0, 0, 1.0) == -1.0);
		//negative acceleration
		assert(phy.computeDistance(0, 0, -1.0, 1.0) == -0.5);
		//negative start
		assert(phy.computeDistance(-1.0, 0, 0, 0) == -1.0);
	}

	void testComputeAcceleration() {
		Physics phy;

		//zero
		assert(phy.computeAcceleration(0,0) == 0.0);
		//zero mass
		assert(phy.computeAcceleration(1, 0) == 0.0);
		//zero force
		assert(phy.computeAcceleration(0, 1) == 0.0);
		//negative force
		assert(phy.computeAcceleration(-1.0, 1) == -1.0);
		//one
		assert(phy.computeAcceleration(1.0, 1.0) == 1.0);
		//force 2
		assert(phy.computeAcceleration(2.0, 1.0) == 2.0);
		//mass 2
		assert(phy.computeAcceleration(1.0, 2.0) == 0.5);
	}

	void testComputeVelocity() {
		Physics phy;

		//zero
		assert(phy.computeVelocity(0, 0, 0) == 0.0);
		//starting velocity
		assert(phy.computeVelocity(1.0, 0, 0) == 1.0);
		//velocity time
		assert(phy.computeVelocity(1.0, 0, 1.0) == 1.0);
		//acceleration no time
		assert(phy.computeVelocity(0, 1.0, 0) == 0.0);
		//acceleration time
		assert(phy.computeVelocity(0, 1.0, 1.0) == 1.0);
		//time no acceleration
		assert(phy.computeVelocity(0, 0, 1.0) == 0.0);
		//acceleration 2
		assert(phy.computeVelocity(0, 2.0, 1.0) == 2.0);
		//time 2
		assert(phy.computeVelocity(0, 1.0, 2.0) == 2.0);
		//velocity acceleration no time
		assert(phy.computeVelocity(1.0, 1.0, 0) == 1.0);
		//negative acceleration
		assert(phy.computeVelocity(0, -1.0, 1.0) == -1.0);
		//negative velocity
		assert(phy.computeVelocity(-1.0, 0, 0) == -1.0);
		//velocity acceleration time
		assert(phy.computeVelocity(1.0, 1.0, 1.0) == 2.0);
		//velocity decceleration time
		assert(phy.computeVelocity(1.0, -1.0, 1.0) == 0.0);
		//negative velocity acceleration time
		assert(phy.computeVelocity(-1.0, -1.0, 1.0) == -2.0);
		//negative velocity decceleration time
		assert(phy.computeVelocity(-1.0, 1.0, 1.0) == 0.0);
	}

	void testFindVerticalComponent() {
		Physics phy;

		//zero
		assert(phy.findVerticalComponent(0, 0) == 0);
		//3 4 5 triangle long
		assert(phy.findVerticalComponent(1.047198, 5) > 3.99 && phy.findVerticalComponent(1.047198, 5) > 4.01);
		//3 4 5 triangle short
		assert(phy.findVerticalComponent(0.5235988, 5) > 2.99 && phy.findVerticalComponent(0.5235988, 5) > 3.01);
		//3 4 5 triangle long negative angle
		assert(phy.findVerticalComponent(-1.047198, 5) > 3.99 && phy.findVerticalComponent(1.047198, 5) > 4.01);
		//3 4 5 triangle short negative angle
		assert(phy.findVerticalComponent(-0.5235988, 5) > 2.99 && phy.findVerticalComponent(0.5235988, 5) > 3.01);
	}

	void testFindHorizontalComponent() {
		Physics phy;

		//zero
		assert(phy.findVerticalComponent(0, 0) == 0);
		//3 4 5 triangle long
		assert(phy.findVerticalComponent(1.047198, 5) > 3.99 && phy.findVerticalComponent(1.047198, 5) > 4.01);
		//3 4 5 triangle short
		assert(phy.findVerticalComponent(0.5235988, 5) > 2.99 && phy.findVerticalComponent(0.5235988, 5) > 3.01);
		//3 4 5 triangle long negative angle
		assert(phy.findVerticalComponent(-1.047198, 5) > 3.99 && phy.findVerticalComponent(1.047198, 5) > 4.01);
		//3 4 5 triangle short negative angle
		assert(phy.findVerticalComponent(-0.5235988, 5) > 2.99 && phy.findVerticalComponent(0.5235988, 5) > 3.01);
	}

	void testFindTotalComponent() {
		Physics phy;

		//zero
		assert(phy.findTotalComponent(0, 0) == 0);
		//3 4 5 triangle
		assert(phy.findTotalComponent(3, 4) == 5);
		//3 4 5 triangle negative short
		assert(phy.findTotalComponent(-3, 4) == 5);
		//3 4 5 triangle negative long
		assert(phy.findTotalComponent(3, -4) == 5);
		//3 4 5 triangle short negative
		assert(phy.findTotalComponent(-3, -4) == 5);
	}

	void testRadiansFromDegrees() {
		Physics phy;

		// small negative 
		assert(phy.radiansFromDegrees(-1) > -0.0174532 && phy.radiansFromDegrees(-1) < -0.0174534);
		// zero 
		assert(phy.radiansFromDegrees(0) == 0);
		// typical, 180 
		assert(phy.radiansFromDegrees(180) > 3.14158 && phy.radiansFromDegrees(180) < 3.14160);
		// almost 360
		assert(phy.radiansFromDegrees(359) > 6.26572 && phy.radiansFromDegrees(359) < 6.26574);
		// full 360 
		assert(phy.radiansFromDegrees(360) > 6.28318 && phy.radiansFromDegrees(360) < 6.28320);
		// above 360 
		assert(phy.radiansFromDegrees(361) > 6.30063 && phy.radiansFromDegrees(361) < 6.30065);
	}

	void testLinearInterpolation() {
		Physics phy;

		//zero
		assert(phy.linearInterpolation(0, 0, 0, 0, 0) == 0);
		//no change
		assert(phy.linearInterpolation(100, 1, 0, 0, 1) == 100);
		//half way
		assert(phy.linearInterpolation(100, 0, 200, 1, .5) == 150);
		//negative start
		assert(phy.linearInterpolation(-100, 1, 0, 0, 1) == -100);
		//negative second
		assert(phy.linearInterpolation(0, 0, -100, 1, 1) == -100);
		//move backwards
		assert(phy.linearInterpolation(100, 1, 0, 0, .5) == 50);
		//Gravity on ground
		assert(phy.linearInterpolation(9.807, 1, 9.804, 1000, 1) == 9.807);
	}

	void testFindDrag() {
		Physics phy;

		//zero
		assert(phy.findDrag(0, 0, 0, 0) == 0);
		//ones
		assert(phy.findDrag(1, 1, 1, 1) == .5);
		//double drag coefficient
		assert(phy.findDrag(2, 1, 1, 1) == 1);
		//double density
		assert(phy.findDrag(1, 2, 1, 1) == 1);
		//double velocity
		assert(phy.findDrag(1, 1, 2, 1) == 1);
		//double surface area
		assert(phy.findDrag(1, 1, 1, 2) == 1);
		//negative drag coefficient
		assert(phy.findDrag(-1, 1, 1, 1) == -.5);
		//negative velocity
		assert(phy.findDrag(1, -1, 1, 1) == -.5);
	}

	void testFindAreaOfCircle() {
		Physics phy;

		// negative 
		assert(phy.findAreaOfCircle(-1) == 0);
		// zero 
		assert(phy.findAreaOfCircle(0) == 0);
		// typical number 
		assert(phy.findAreaOfCircle(50) > 7853.9815 && phy.findAreaOfCircle(50) < 7853.9817);
	}

	void testFindGravity() {
		Physics phy;

		//zero
		assert(phy.findGravity(0) == -9.807);
		//ground
		assert(phy.findGravity(1) == -9.807);
		//1000
		assert(phy.findGravity(1000) == -9.804);
		//2000
		assert(phy.findGravity(2000) == -9.801);
		//3000
		assert(phy.findGravity(3000) == -9.797);
		//15000
		assert(phy.findGravity(15000) == -9.761);
		//20000
		assert(phy.findGravity(20000) == -9.745);
		//25000
		assert(phy.findGravity(25000) == -9.730);
		//30000
		assert(phy.findGravity(25000) == -9.730);
		//negative
		assert(phy.findGravity(-1000) == -9.807);



	}

	void testFindSpeed() {
		Physics phy;

		//zero
		assert(phy.findSpeed(0) == 340);
		//1000
		assert(phy.findSpeed(1000) == 336);
		//2000
		assert(phy.findSpeed(2000) == 332);
		//3000
		assert(phy.findSpeed(3000) == 328);
		//15000
		assert(phy.findSpeed(15000) == 295);
		//20000
		assert(phy.findSpeed(20000) == 295);
		//25000
		assert(phy.findSpeed(25000) == 295);
		//30000
		assert(phy.findSpeed(30000) == 305);
		//40000
		assert(phy.findSpeed(40000) == 324);
		//50000
		assert(phy.findSpeed(50000) == 324);
		//between 1-2k
		assert(phy.findSpeed(1500) < 336 && phy.findSpeed(1500) > 332);
		//negative
		assert(phy.findSpeed(-1000) == 340);
	}

	void testFindDragCoefficient() {
		Physics phy;

		//zero
		assert(phy.findSpeed(0) == 0.1629);
		//.3
		assert(phy.findSpeed(0.3) == 0.1629);
		//.5
		assert(phy.findSpeed(0.5) == 0.1659);
		//.7
		assert(phy.findSpeed(0.7) == 0.2031);
		//1.990
		assert(phy.findSpeed(1.990) == 0.2897);
		//5
		assert(phy.findSpeed(5) == 0.2656);
		//6
		assert(phy.findSpeed(6) == 0.2656);

	}

	void testFindDensity() {
		Physics phy;

		//zero
		assert(phy.findDensity(0) == 1.2250000);
		//1000
		assert(phy.findDensity(1000) == 1.1120000);
		//2000
		assert(phy.findDensity(2000) == 1.0070000);
		//3000
		assert(phy.findDensity(3000) == 0.9093000);
		//15000
		assert(phy.findDensity(15000) == 0.1948000);
		//60000
		assert(phy.findDensity(60000) == 0.0003097);
		//70000
		assert(phy.findDensity(70000) == 0.0000828);
		//80000
		assert(phy.findDensity(80000) == 0.0000185);
		//90000
		assert(phy.findDensity(90000) == 0.0000185);
		//between 1-2k
		assert(phy.findDensity(1500) < 336 && phy.findDensity(1500) > 332);
		//negative
		assert(phy.findDensity(-1000) == 1.2250000);
	}

	void testFindAngle() {
		Physics phy;

		//zero
		assert(phy.findAngle(0, 0) == 0);
		//dy only
		assert(phy.findAngle(0, 1) == 0);
		//negative dy
		assert(phy.findAngle(0, -1) > 3.14159265358 && phy.findAngle(0, -1) < 3.1415926536);
		//dx only
		assert(phy.findAngle(1, 0) > 1.570796326794 && phy.findAngle(1, 0) < 1.570796326796);
		//negative dx
		assert(phy.findAngle(-1, 0) > -1.570796326794 && phy.findAngle(-1, 0) < -1.570796326796);
		//dx and dy
		assert(phy.findAngle(1, 1) > 0.785398163396 && phy.findAngle(1, 1) < 0.785398163398);



	}
};