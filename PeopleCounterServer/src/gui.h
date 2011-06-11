#pragma once

//#include "network.h"
#include "ofMain.h"
#include "defines.h"

class Gui {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
	ofColor aColor;
	
	
	// analyzer variables
	int		depthThreshold;
	int		blur;
	
	// network variables
	int		slave1id;
	int		slave2id;
	int		slave3id;
	
    int clientOffset[NUM_CLIENTS];

	
};
