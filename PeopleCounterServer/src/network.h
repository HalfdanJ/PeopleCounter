#pragma once


//#include "tracker.h"
#include "ofxOsc.h"

class Network {
public:
	void setup();
	void update();
	void debugDraw();
	
//	Tracker * tracker;
	
	ofxOscSender oscSender[3];
	ofxOscReceiver oscReceiver[3];

	void connectToClient(int client);
	
	bool clientConnected[3];	
	int clientTimeout[3];
	long clientReconnect[3];
		long clientPing[3];
};