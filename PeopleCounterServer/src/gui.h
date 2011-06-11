#pragma once

//#include "network.h"
#include "ofMain.h"
#include "analyzer.h"


class Gui {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
	ofColor aColor;
	
	
	// analyzer variables
	int		depthThreshold;
	
	// network variables
	int		slave1id;
	int		slave2id;
	int		slave3id;
	
	
	
};
