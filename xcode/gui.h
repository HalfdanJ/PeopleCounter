#pragma once

#include "kinect.h"
#include "tracker.h"
#include "synth.h"


class Gui {
public:
	void setup(Kinect* kinectRef, Tracker * trackerRef);
	void update();
	void draw();
	
	void keyPressed(int key);
	
	Kinect * kinect;
	Tracker * tracker;
	Synth * synth;
	
	int		heightThreshold;
	
};
