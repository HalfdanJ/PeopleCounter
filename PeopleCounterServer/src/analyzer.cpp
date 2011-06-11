#include "analyzer.h"

void Analyzer::setup(){
}


void Analyzer::update(){

}


void Analyzer::debugDraw(){
	//cout<<blobData.size()<<endl;
	ofSetColor(255, 0, 0);
	for(int i=0;i<blobData[0].size();i++){
		ofRect(blobData[0][i].x-5, blobData[0][i].y-5, 10, 10);
		ofDrawBitmapString(ofToString(blobData[0][i].bid, 0), blobData[0][i].x+12, blobData[0][i].y);
	}
	
}
