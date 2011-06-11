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
	
	int		heightThreshold;
	int		slave1id;
	int		slave2id;
	int		slave3id;
	
};
