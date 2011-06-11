/* -*- Mode: C; tab-width: 4 -*- */
#include "tracker.h"

void Tracker::setup(Kinect* kinectRef){
	kinect = kinectRef;
	
	grayImage.allocate(640,480);
	grayImageThreshold.allocate(640,480);
	threshold = 80;
	movement_threshold = 40;
	blur = 0;
	
	next_id = 0;
}


void Tracker::update(){
	if(kinect->kinect.isFrameNew()){
		blobData = vector<blob_data>();
		
		int blobsIdentified = 0; // Unused as of yet. 
		
		grayImage.setFromPixels(kinect->kinect.getDepthPixels(), 640, 480);
		grayImageThreshold = grayImage;
		grayImageThreshold.threshold(threshold, false);
		if(blur > 0){
			grayImageThreshold.blur(blur);
		}
		
		contourFinder.findContours(grayImageThreshold, 10, (640*480)/2, 20, false);    
		
		for(int i=0;i<contourFinder.nBlobs;i++){
			ofxCvBlob blobClass = contourFinder.blobs[i];
			blob_data blob; /* = malloc(sizeof(blob_data)); */
			
			blob.x = blobClass.centroid.x;
			blob.y = blobClass.centroid.y;
			blob.bid = -1;
			
			// Looping through last frame's blobs to match these new ones
			// to the old ones, and to apply their IDs.
			for(int i=0; i < oldBlobs.size(); i++) {
				
				// Checks the centroid of an oldBlob, and checks if its 
				// distance to the current blob is less than the threshold.
				// If it is, then it's safe to let it have the old one's ID.
				if (ofDistSquared(blob.x, blob.y, oldBlobs[i].x, oldBlobs[i].y) < movement_threshold) {
					blob.bid = oldBlobs[i].bid;
					blobsIdentified++;
					break;
				}
			}
			
			// Check if the blob hasn't been matched with an old one. It
			// means we have found a new person.
			if (blob.bid == -1) {
				//		  cout<<next_id<<endl;
				blob.bid = next_id++;
			}
			
			// At this point any blob has x and y coordinates for its
			// centroid, plus an ID, either inherited or new.
			blobData.push_back(blob);
		}
		
		// Update the oldBlobs datastructure to giv
		oldBlobs = blobData;
	}
}


void Tracker::debugDraw(){
	ofSetColor(255, 255, 255);
	grayImage.draw(640,0,320,240);
	grayImageThreshold.draw(640+320,0,320,240);
	contourFinder.draw(640, 0, 320, 240);
	
	//cout<<blobData.size()<<endl;
	ofSetColor(255, 0, 0);
	for(int i=0;i<blobData.size();i++){
		ofRect(blobData[i].x-5, blobData[i].y-5, 10, 10);
		ofDrawBitmapString(ofToString(blobData[i].bid, 0), blobData[i].x+12, blobData[i].y);
	}
}
