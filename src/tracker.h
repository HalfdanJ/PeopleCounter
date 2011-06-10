#pragma once

#include "kinect.h"

class Tracker {
public:
	void setup(Kinect* kinectRef);
	void update();
	void debugDraw();
	
	Kinect * kinect;
};