#pragma once

#include "kinect.h"
#include "tracker.h"




class Gui {
public:
	void setup(Kinect* kinectRef, Tracker * trackerRef);
	void update();
	void draw();
	
	Kinect * kinect;
	Tracker * tracker;
	
	int		heightThreshold;
	
};