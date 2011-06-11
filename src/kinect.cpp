#include "kinect.h"

void Kinect::setup(){
	kinect.init(false, false, true);
	kinect.setVerbose(true);
	kinect.open();
}


void Kinect::update(){
	kinect.update();
}


void Kinect::debugDraw(){
	kinect.drawDepth(0,0,640,480);
}
