#pragma once

#include "kinect.h"
#include "ofxOpenCv.h"

struct blob_data {
	int bid;
	float x;
	float y;
	float w;
	float h;
	ofxCvBlob cvBlob;
	float blobDiff;
};

class Tracker {
public:
	void setup(Kinect* kinectRef);
	void update();
	void debugDraw();
	
	Kinect * kinect;
	
	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage grayImageThreshold;
	
	ofxCvContourFinder contourFinder;
	
	int threshold;
	int movement_threshold;
	int blur;
    
    int topCrop;
    int bottomCrop;
    int leftCrop;
    int rightCrop;
	
	vector<blob_data> blobData;

	int next_id;
	
	float minSize, maxSize;

	void crop();
private:
	vector<blob_data> oldBlobs;
};
