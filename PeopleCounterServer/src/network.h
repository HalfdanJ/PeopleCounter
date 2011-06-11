#pragma once

#include "ofMain.h"
#include "ofxTCPClient.h"

class Network {
public:
	void setup();
	void update();
	void debugDraw();
	
//	Tracker * tracker;
	
	ofxTCPClient TCP[3];


	void connectToClient(int client);
	
	bool clientConnected[3];	
	int clientTimeout[3];
	long clientReconnect[3];
		long clientPing[3];
	
	void receiveMessage(string messsage, int client);

};