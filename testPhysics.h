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

	}

	void testRadiansFromDegrees() {

	}

	void testLinearInterpolation() {

	}

	void testFindDrag() {

	}

	void testFindAreaOfCircle() {

	}

	void testFindGravity() {

	}

	void testFindSpeed() {

	}

	void testFindDragCoefficient() {

	}

	void testFindDensity() {

	}

	void testFindAngle() {

	}
	void testGetHistory() {

	}
};