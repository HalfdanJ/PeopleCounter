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

//Is called by network when new data is incomming. 
//Here we delete blobs that where not present in the last frame
void Analyzer::markNewFrame(int client){
   // blobData[client].clear();
    for(int i=0;i<blobData[client].size();i++){
        if(!blobData[client][i].inFrame){
            blobData[client].erase(blobData[client].begin()+i);
        }
    }

    for(int i=0;i<blobData[client].size();i++){
        blobData[client][i].inFrame = false;
    }
}

//Is called by network every time it receives a new packet
void Analyzer::addBlobData(blob_data newData, int client){
    bool blobFound = false;
    for(int i=0;i<blobData[client].size();i++){
        //Check if the blob id (bid) is already in the vector, then just update the data
        if(blobData[client][i].bid == newData.bid){
            blobFound = true;
            blobData[client][i].x = newData.x;
            blobData[client][i].y = newData.y;
            blobData[client][i].w = newData.w;
            blobData[client][i].h = newData.h;
            blobData[client][i].inFrame = true;
            break;
        }
    }

    if(!blobFound){        
        //If the blob was not already in the vector, lets add it and give it some birth information
        newData.birth = ofGetElapsedTimeMillis();
        newData.birthX = newData.x;
        newData.birthY = newData.y;
        newData.isCounted = false;
        newData.inFrame = true;
        
        blobData[client].push_back(newData);   
    }
    
}