#pragma once

#include "ofMain.h"
#include "ofxTCPClient.h"

#include "analyzer.h"
#include "gui.h"
#include "defines.h"


class Network {
public:
	void setup(Analyzer * analyzer, Gui * gui);
	void update();
	void debugDraw();
	
//	Tracker * tracker;
	Analyzer * analyzer;
	Gui * gui;
	
	ofxTCPClient TCP[NUM_CLIENTS];


	void connectToClient(int client);
	
	bool clientConnected[NUM_CLIENTS];	
	int clientTimeout[NUM_CLIENTS];
	long clientReconnect[NUM_CLIENTS];
		long clientPing[NUM_CLIENTS];
	
	void receiveMessage(string messsage, int client);
	bool sendMessage(int client);

	blob_data bufferObject[NUM_CLIENTS];
	
	long long sendTimer[NUM_CLIENTS];
};