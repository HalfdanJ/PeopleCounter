#include "tracker.h"

void Tracker::setup(Kinect* kinectRef){
	kinect = kinectRef;
	
	grayImage.allocate(640,480);
	grayImageThreshold.allocate(640,480);
	threshold = 80;
}


void Tracker::update(){
	if(kinect->kinect.isFrameNew()){
		grayImage.setFromPixels(kinect->kinect.getDepthPixels(), 640, 480);
		grayImageThreshold = grayImage;
		grayImageThreshold.threshold(threshold, false);
		contourFinder.findContours(grayImageThreshold, 10, (640*480)/2, 20, false);
		
		for(int i=0;i<contourFinder.nBlobs;i++){
			ofxCvBlob blob = contourFinder.blobs[i];
			
		}
	}
}


void Tracker::debugDraw(){
	grayImage.draw(640,0,320,240);
	grayImageThreshold.draw(640+320,0,320,240);
	contourFinder.draw(640, 0, 320, 240);

}
