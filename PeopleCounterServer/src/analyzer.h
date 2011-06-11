#pragma once

#include "ofMain.h"
#include "gui.h"
#include "defines.h"

struct blob_data {
	int bid;
	float x;
	float y;
    float w;
    float h;
};




class Analyzer {
public:
	void setup(Gui * gui);
	void update();
	void debugDraw();
	
    Gui * gui;
	vector< blob_data > blobData[NUM_CLIENTS];
    

};