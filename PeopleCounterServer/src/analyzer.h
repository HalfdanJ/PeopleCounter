#pragma once

#include "ofMain.h"

struct blob_data {
	int bid;
	float x;
	float y;
};




class Analyzer {
public:
	void setup();
	void update();
	void debugDraw();
	
	vector< blob_data > blobData[3];

};