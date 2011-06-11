/* -*- Mode: C; tab-width: 4 -*- */
#include "tracker.h"

void Tracker::setup(Kinect* kinectRef){
  kinect = kinectRef;
	
  grayImage.allocate(640,480);
  grayImageThreshold.allocate(640,480);
  threshold = 80;

  next_id = 0;
}


void Tracker::update(){
  if(kinect->kinect.isFrameNew()){
	int blobsIdentified = 0; // Unused as of yet. 

    grayImage.setFromPixels(kinect->kinect.getDepthPixels(), 640, 480);
    grayImageThreshold = grayImage;
    grayImageThreshold.threshold(threshold, false);
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
		blob.bid = next_id++;
	  }
	  
	  // At this point any blob has x and y coordinates for its
	  // centroid, plus an ID, either inherited or new.
	  blobData.push_back(blob);
    }

	// Update the oldBlobs datastructure to giv
	oldBlobs = blobData;
	blobData = vector<blob_data>();
  }
}


void Tracker::debugDraw(){
  grayImage.draw(640,0,320,240);
  grayImageThreshold.draw(640+320,0,320,240);
  contourFinder.draw(640, 0, 320, 240);

}
