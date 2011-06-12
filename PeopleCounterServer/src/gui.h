#pragma once

#include "ofMain.h"
#include "defines.h"

class Gui {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
		
	// analyzer
	int		depthThreshold;
	int		blur;	
	bool	addPerson;
	
	// network
    int clientOffset[NUM_CLIENTS];

	// synth 
	bool playAudio;
	
};
