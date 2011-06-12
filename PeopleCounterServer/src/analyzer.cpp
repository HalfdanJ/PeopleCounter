#include "analyzer.h"

void Analyzer::setup(Gui * guiRef){
    gui = guiRef;
	
	count = 0;
    
    onePersonArea = 40000;
    addedCount = 0;
}

int combined_id;

void Analyzer::update(){
    addedCount = 0;
    
    if(gui->addPerson) {
		gui->addPerson = false;
		count += 1;
	}
    
    for(int u=0;u<combinedBlobs.size();u++){
        combinedBlobs[u].foundInThisFrame = false;
    }
    
    for(int client=0;client<NUM_CLIENTS;client++){
        for(int i=0;i<blobData[client].size();i++){
            //Go through all new data
            bool alreadyAdded = false;

            for(int u=0;u<combinedBlobs.size();u++){
                //Check if bid is already in the combined blob
                int bestBirth = -1;
                for(int j=0;j<combinedBlobs[u].childrenBid.size();j++){
                    if(combinedBlobs[u].childrenBid[j] == blobData[client][i].bid){
                        combinedBlobs[u].foundInThisFrame = true;
                        
                        //The bid is here
                        if(bestBirth == -1 || bestBirth > blobData[client][i].birth){
                            //The blob is the oldes so far, so it updates the combined blob's position
                            combinedBlobs[u].x = blobData[client][i].x + gui->clientOffsetX[client];
                            combinedBlobs[u].y = blobData[client][i].y + gui->clientOffsetY[client];
                            combinedBlobs[u].w = blobData[client][i].w;
                            combinedBlobs[u].h = blobData[client][i].h; 
                            combinedBlobs[u].birth = blobData[client][i].birth;
                            bestBirth = blobData[client][i].birth;
                        }
                        alreadyAdded = true;
                        break;
                    }
                }

            }
            
            if(!alreadyAdded){
            //if the blob was not already in a combined blobs list over bids, lets see if it should be    
                for(int u=0;u<combinedBlobs.size();u++){
                    //Check if already added by another client
                    if(ofDist(combinedBlobs[u].x, 
                              combinedBlobs[u].y, 
                              blobData[client][i].x+gui->clientOffsetX[client], 
                              blobData[client][i].y+gui->clientOffsetY[client]) < gui->analyzerMergeDist){

                        combinedBlobs[u].foundInThisFrame = true;
                        
                        //Add it to the list over bids
                        combinedBlobs[u].childrenBid.push_back(blobData[client][i].bid);

                        if(combinedBlobs[u].birth > blobData[client][i].birth){
                            //If this blob is older, so lets use that one
                            combinedBlobs[u].x = blobData[client][i].x + gui->clientOffsetX[client];
                            combinedBlobs[u].y = blobData[client][i].y + gui->clientOffsetY[client];
                            combinedBlobs[u].w = blobData[client][i].w;
                            combinedBlobs[u].h = blobData[client][i].h; 
                            combinedBlobs[u].birth = blobData[client][i].birth;
                        }
                        alreadyAdded = true;
                    }               
                }
            }
            
            
            if(!alreadyAdded){
                //If the blob is not already added, we make a new combined blob
                combinedBlobs.push_back(blobData[client][i]);   
                combinedBlobs[combinedBlobs.size()-1].x += gui->clientOffsetX[client];
                combinedBlobs[combinedBlobs.size()-1].y += gui->clientOffsetY[client];
                combinedBlobs[combinedBlobs.size()-1].birthX += gui->clientOffsetX[client];
                combinedBlobs[combinedBlobs.size()-1].birthY += gui->clientOffsetY[client];

                combinedBlobs[combinedBlobs.size()-1].childrenBid.push_back(blobData[client][i].bid);
                combinedBlobs[combinedBlobs.size()-1].foundInThisFrame = true;
            } 
        }
    }
    
    //Lets see if some of the combined blobs have dissapeard
    for(int u=0;u<combinedBlobs.size();u++){
        if(!combinedBlobs[u].foundInThisFrame){
            combinedBlobs.erase(combinedBlobs.begin()+u);
        }
    }
    
    
    //Lets see if we should count some blobs!
    for(int i=0;i<combinedBlobs.size();i++){
        if(!combinedBlobs[i].isCounted){
            //If the blob is older then 1 sec
            if(combinedBlobs[i].birth < ofGetElapsedTimeMillis() - 500){
                //The distance the blob has gone
                if(fabs(combinedBlobs[i].birthY - combinedBlobs[i].y) > 80){
                    combinedBlobs[i].isCounted = true;
                    int persons = floor((combinedBlobs[i].w*combinedBlobs[i].h) / onePersonArea);
                    if(persons < 1)
                        persons = 1;
                    count+=persons;
                    addedCount += persons;
                }
            }
        }
    }

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
        glTranslated(gui->clientOffsetX[i], gui->clientOffsetY[i], 0);
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
        glTranslated(gui->clientOffsetX[i], gui->clientOffsetY[i], 0);

        //Draw blobs directly from clients
        ofSetColor(255, 0, 0,100);    
        for(int u=0;u<blobData[i].size();u++){
            ofNoFill();
            ofRect(blobData[i][u].x-blobData[i][u].w*0.5, 
                   blobData[i][u].y-blobData[i][u].h*0.5, 
                   blobData[i][u].w, 
                   blobData[i][u].h);
            ofDrawBitmapString(ofToString(blobData[i][u].bid, 0), blobData[i][u].x, blobData[i][u].y);
        }
        
               

        glPopMatrix();
	}
    
    
    glPushMatrix();{
        glScaled(0.5, 0.5, 1.0);
        
        for(int i=0;i<combinedBlobs.size();i++){
            if(combinedBlobs[i].isCounted){
                ofSetColor(0, 255, 0);    
            } else {
                ofSetColor(0, 0, 255);    
            }
            ofNoFill();
            ofRect(combinedBlobs[i].x-combinedBlobs[i].w*0.5, 
                   combinedBlobs[i].y-combinedBlobs[i].h*0.5, 
                   combinedBlobs[i].w, 
                   combinedBlobs[i].h);
            float dist = fabs(combinedBlobs[i].birthY - combinedBlobs[i].y);
            float area = combinedBlobs[i].w*combinedBlobs[i].h;
            ofDrawBitmapString(ofToString(combinedBlobs[i].bid, 0)+
                               "\ndist: "+ofToString(dist,0)+
                               "\nsize: "+ofToString(area,0)+ " (="+ofToString(area/onePersonArea,1)+" person)", 
                               combinedBlobs[i].x, combinedBlobs[i].y);
            
            ofLine(combinedBlobs[i].birthX, combinedBlobs[i].birthY, combinedBlobs[i].x, combinedBlobs[i].y);
        }        
    }glPopMatrix();
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Total count: "+ofToString(count), ofGetWidth()-200, -20);

    
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