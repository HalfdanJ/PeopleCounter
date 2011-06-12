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
	leftCrop = 0;
	bottomCrop = 0;
	rightCrop = 0;
	topCrop = 0;
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
	int nPts = old->cvBlob.nPts;
	gpc_vertex * old_p_arr = (gpc_vertex *) malloc(sizeof(gpc_vertex)*nPts);
	
	
	old_p_list.vertex = old_p_arr;
	
	cvBlob2Polygon(&old->cvBlob, &old_p);
	
	gpc_polygon cur_p;
	gpc_vertex_list cur_p_list;
	cur_p.contour = &cur_p_list;
	nPts = cur->cvBlob.nPts;
	gpc_vertex * cur_p_arr = (gpc_vertex *) malloc(sizeof(gpc_vertex)*nPts);
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
		
		
		
		//grayImageThreshold.setROI(leftCrop, topCrop, (640-leftCrop)- rightCrop, (480-topCrop)- bottomCrop);
		
		crop();
		
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
			for(int j=0; j < oldBlobs.size(); j++) {
				
				// Checks the centroid of an oldBlob, and checks if its 
				// distance to the current blob is less than the threshold.
				// If it is, then it's safe to let it have the old one's ID.
				
				//if (ofDistSquared(blob.x, blob.y, oldBlobs[i].x, oldBlobs[i].y) < movement_threshold) {
				if (blobsEqual(&blob, &oldBlobs[j], 1.1)) {
					if(blob.bid==-1){
						blob.bid = oldBlobs[j].bid;
						if (oldBlobs[j].secondaryIt && oldBlobs[j].secondaryBids.size() > 0) {							
							oldBlobs[j].bid = oldBlobs[j].secondaryBids[0];
							blob.bid = oldBlobs[j].bid;

							oldBlobs[j].secondaryBids.erase(oldBlobs[j].secondaryBids.begin());
							for(int k=0;k<blobData.size();k++){
								for(int l=0;l<blobData[k].secondaryBids.size();l++){
									if(blobData[k].secondaryBids[l] == blob.bid){
										blobData[k].secondaryBids.erase(blobData[k].secondaryBids.begin()+l);
									}
								}
							}
						}
						
						oldBlobs[j].secondaryIt = true;
						
						blob.secondaryBids = oldBlobs[j].secondaryBids;


						blobsIdentified++;
					} else {
						bool found = false;
						for(int l=0;l<blob.secondaryBids.size();l++){
							if(blob.secondaryBids[l] == oldBlobs[j].bid)
								found = true;
							break;
						}

					//	if(!found){
							blob.secondaryBids.push_back(oldBlobs[j].bid);						
						//	blob.secondaryBids.insert(blob.secondaryBids.end(), oldBlobs[j].secondaryBids.begin(), oldBlobs[j].secondaryBids.end());
					//	}
					}
				}
				
			}
			
			// Check if the blob hasn't been matched with an old one. It
			// means we have found a new person.
			if (blob.bid == -1) {
				//		  cout<<next_id<<endl;
				blob.bid = next_id++;
			}
			
			blob.secondaryIt = false;
			
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
		string str = ofToString(blobData[i].bid, 0);
		for(int j=0;j<blobData[i].secondaryBids.size();j++){
		//	cout<<"yay sec "<<j<<endl;
			str += "\n"+ofToString(blobData[i].secondaryBids[j], 0);
		}
		
		ofDrawBitmapString(str, blobData[i].x+12, blobData[i].y);
	}
	
	ofNoFill();
	ofSetColor(255,0,0);
	ofRect(leftCrop, topCrop, (640-leftCrop)- rightCrop, (480-topCrop)- bottomCrop);
}

void Tracker::crop(){
	int nPoints = 4;
	CvPoint _cp[4];
	_cp[0].x = 0; _cp[0].y = 0;
	_cp[1].x = leftCrop; _cp[1].y = 0;
	_cp[2].x = leftCrop; _cp[2].y = 480;
	_cp[3].x = 0; _cp[3].y = 480;
	
	CvPoint * cp = _cp;
	cvFillPoly(grayImage.getCvImage(), &cp, &nPoints, 1, cvScalar(0,0,0,10));
	
	_cp[0].x = 640-rightCrop; _cp[0].y = 0;
	_cp[1].x = 640; _cp[1].y = 0;
	_cp[2].x = 640; _cp[2].y = 480;
	_cp[3].x = 640-rightCrop; _cp[3].y = 480;
	cp = _cp;
	cvFillPoly(grayImage.getCvImage(), &cp, &nPoints, 1, cvScalar(0,0,0,10));
	
	
	_cp[0].x = 0; _cp[0].y = 0;
	_cp[1].x = 640; _cp[1].y = 0;
	_cp[2].x = 640; _cp[2].y = topCrop;
	_cp[3].x = 0; _cp[3].y = topCrop;
	cp = _cp;
	cvFillPoly(grayImage.getCvImage(), &cp, &nPoints, 1, cvScalar(0,0,0,10));
	
	_cp[0].x = 0; _cp[0].y = 480-bottomCrop;
	_cp[1].x = 640; _cp[1].y = 480-bottomCrop;
	_cp[2].x = 640; _cp[2].y = 480;
	_cp[3].x = 0; _cp[3].y = 480;
	cp = _cp;
	cvFillPoly(grayImage.getCvImage(), &cp, &nPoints, 1, cvScalar(0,0,0,10));
	
	grayImage.flagImageChanged();
}
