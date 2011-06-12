/* -*- Mode: C; tab-width: 4 -*- */
#include "tracker.h"
#include "gpc.h"
#include "gpc.c"

void Tracker::setup(Kinect* kinectRef){
	kinect = kinectRef;
	
	grayImage.allocate(640,480);
	grayImageThreshold.allocate(640,480);
	threshold = 255;
	movement_threshold = 40;
	blur = 30;
	
	next_id = 0;

	minSize = 20;
	maxSize = (640*480)/2;
}

void cvBlob2Polygon(ofxCvBlob* blob, gpc_polygon* output) {
	
	
	output->num_contours = 1;
	output->hole = false;
	
	
	output->contour->num_vertices = blob->nPts;
//	vertices.vertex = (gpc_vertex*) malloc(sizeof(gpc_vertex)*blob->nPts);
	
	for(int i = 0; i<blob->nPts; i++) {
		gpc_vertex curPoint;
		curPoint.x = blob->pts[i].x;
		curPoint.y = blob->pts[i].y;
		
		output->contour->vertex[i] = curPoint;
	}
	
	//output->contour = &vertices;
}

bool blobsEqual(blob_data* old, blob_data* cur, float threshold) {
	gpc_polygon result;
	
	gpc_polygon old_p;
	gpc_vertex_list old_p_list;
	old_p.contour = &old_p_list;
	gpc_vertex old_p_arr[old->cvBlob.nPts];
	old_p_list.vertex = old_p_arr;
	
	cvBlob2Polygon(&old->cvBlob, &old_p);
	
	gpc_polygon cur_p;
	gpc_vertex_list cur_p_list;
	cur_p.contour = &cur_p_list;
	gpc_vertex cur_p_arr[cur->cvBlob.nPts];
	cur_p_list.vertex = cur_p_arr;

	
	cvBlob2Polygon(&cur->cvBlob, &cur_p);
	
	gpc_polygon_clip(GPC_INT, &old_p, &cur_p, &result);
	
	float avg = (old->cvBlob.nPts + cur->cvBlob.nPts)/2.0;
	
	
	if(result.num_contours == 0)
		return false;
	

	float diff = fabs(1 - avg / result.contour->num_vertices);
	
	return diff <= threshold;
	
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
		
		contourFinder.findContours(grayImageThreshold, minSize, maxSize, 20, false);    
		
		for(int i=0;i<contourFinder.nBlobs;i++){
			ofxCvBlob blobClass = contourFinder.blobs[i];
			blob_data blob; /* = malloc(sizeof(blob_data)); */
			
			blob.x = blobClass.centroid.x;
			blob.y = blobClass.centroid.y;
			blob.bid = -1;
			blob.w = blobClass.boundingRect.width;
			blob.h = blobClass.boundingRect.height;
			blob.cvBlob = contourFinder.blobs[i];
			blob.blobDiff = 10;
			
			// Looping through last frame's blobs to match these new ones
			// to the old ones, and to apply their IDs.
			for(int i=0; i < oldBlobs.size(); i++) {
				
				// Checks the centroid of an oldBlob, and checks if its 
				// distance to the current blob is less than the threshold.
				// If it is, then it's safe to let it have the old one's ID.
				
				//if (ofDistSquared(blob.x, blob.y, oldBlobs[i].x, oldBlobs[i].y) < movement_threshold) {
				if (blobsEqual(&blob, &oldBlobs[i], 1.1)) {
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
		ofDrawBitmapString(ofToString(blobData[i].bid, 0)+"\ndiff: "+ofToString(blobData[i].blobDiff,4), blobData[i].x+12, blobData[i].y);
	}
}
