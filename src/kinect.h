#pragma once

#include "ofxKinect.h"

class Kinect {
public:
	void setup();
	void update();
	void debugDraw();
	
	ofxKinect kinect[2];
};