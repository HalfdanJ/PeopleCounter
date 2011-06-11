#pragma once


#include "tracker.h"
#include "ofxTCPServer.h"

class Network {
public:
	void setup(Tracker* trackerRef);
	void update();
	void debugDraw();
	
	Tracker * tracker;
	
	ofxTCPServer TCP;

//	void connectToServer();
	
	bool serverConnected;
	
	int myId;
	string serverIp;
	
	int timeout;
	
	void receiveMessage(string messsage);
	void sendMessage(int client);
};