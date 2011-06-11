#include "analyzer.h"

void Analyzer::setup(Gui * guiRef){
    gui = guiRef;
}


void Analyzer::update(){

}


void Analyzer::debugDraw(){
	//cout<<blobData.size()<<endl;
    ofEnableAlphaBlending();
    glPushMatrix();
    glTranslated(20, ofGetHeight()-240-70-20, 0);
    
    float w = 1024 - 40;
    float h = 240;
    
    ofFill();
    ofSetColor(40, 40, 40);
    ofRect(0, 0, w, h);
    ofNoFill();
    ofSetColor(70, 70, 70);
    ofRect(0, 0, w, h);    
    
    for(int i=0;i<NUM_CLIENTS;i++){
        glPushMatrix();
        glScaled(0.5, 0.5, 1.0);
        glTranslated(gui->clientOffset[i], 0, 0);
        ofFill();
        ofSetColor(50, 50, 70,100);
        ofRect(0, 0, 640, 480);
        ofNoFill();
        ofSetColor(80, 80, 100,100);
        ofRect(0, 0, 640, 480);
        ofSetColor(255, 255, 255,120);
        
        ofDrawBitmapString("Client "+ofToString(i), 10, 25);
        glPopMatrix();

    }

	
    for(int i=0;i<NUM_CLIENTS;i++){
        glPushMatrix();
        glScaled(0.5, 0.5, 1.0);
        glTranslated(gui->clientOffset[i], 0, 0);

        //Draw blobs
        for(int u=0;u<blobData[i].size();u++){
            ofSetColor(255, 0, 0);    
            ofNoFill();
            ofRect(blobData[i][u].x-blobData[i][u].w*0.5, 
                   blobData[i][u].y-blobData[i][u].h*0.5, 
                   blobData[i][u].w, 
                   blobData[i][u].h);
            ofDrawBitmapString(ofToString(blobData[i][u].bid, 0), blobData[i][u].x, blobData[i][u].y);
        }
        

        glPopMatrix();
	}
    
    glPopMatrix();
	
}
