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
	bool	addPerson;
    float   analyzerMergeDist;    

    //Client
	int		blur;	
    int     minBlobSize;
    int     maxBlobSize;

	// network
    int clientOffsetX[NUM_CLIENTS];
    int clientOffsetY[NUM_CLIENTS];
    
    int leftCrop[NUM_CLIENTS];
    int rightCrop[NUM_CLIENTS];
    int topCrop;
    int bottomCrop;
    

	// synth 
	bool playAudio;
	
};
