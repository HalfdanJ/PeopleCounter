#pragma once

#include "ofMain.h"
#include "ofxTCPClient.h"

#include "analyzer.h"

class Network {
public:
	void setup(Analyzer * analyzer);
	void update();
	void debugDraw();
	
//	Tracker * tracker;
	Analyzer * analyzer;
	
	ofxTCPClient TCP[3];


	void connectToClient(int client);
	
	bool clientConnected[3];	
	int clientTimeout[3];
	long clientReconnect[3];
		long clientPing[3];
	
	void receiveMessage(string messsage, int client);
	bool sendMessage(int client);

	blob_data bufferObject;
};