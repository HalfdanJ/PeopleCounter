#include "kinect.h"

void Kinect::setup(){
	kinect.init(false, false, true);
	kinect.kindex = 0;
	kinect.setVerbose(true);
	kinect.open();
}


void Kinect::update(){
	kinect.update();
}


void Kinect::debugDraw(){
	ofSetColor(255, 255, 255);
	kinect.drawDepth(0,0,640,480);
}
