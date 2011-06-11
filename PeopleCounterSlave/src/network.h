#pragma once


#include "tracker.h"
#include "ofxOsc.h"

class Network {
public:
	void setup(Tracker* trackerRef);
	void update();
	void debugDraw();
	
	Tracker * tracker;
	
	ofxOscSender oscSender;
	ofxOscReceiver oscReceiver;

	void connectToServer();
	
	bool serverConnected;
	
	int myId;

	int timeout;
};