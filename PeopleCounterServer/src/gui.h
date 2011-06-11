#pragma once

//#include "network.h"
#include "analyzer.h"


class Gui {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	
	int		heightThreshold;
	
};
