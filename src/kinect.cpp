#include "kinect.h"

void Kinect::setup(){
	for(int i=0;i<2;i++){
		kinect[i].init(false, false);
		kinect[i].kindex = i;
		kinect[i].setVerbose(true);
		kinect[i].open();

	}
}


void Kinect::update(){
	for(int i=0;i<2;i++){
		kinect[i].update();
	}		
}


void Kinect::debugDraw(){
	for(int i=0;i<2;i++){
		kinect[i].drawDepth(240*i,0,320,240);

	}		
}
