#include "network.h"

void Network::setup(Analyzer * analyzeRef, Gui * guiRef){
	analyzer = analyzeRef;
	gui = guiRef; 
	
	for(int i=0;i<NUM_CLIENTS;i++){
		clientConnected[i] = false;
		clientTimeout[i] = 500;
		clientReconnect[i] = 0;
		clientPing[i] = 0;
	}
	
	TCP[0].setup("192.38.71.110", 1111);
    TCP[1].setup("192.38.71.161", 1111);

//	TCP[0].setup("localhost", 1111);
//    	TCP[0].setup("halfdanjmacbook.local", 1111);
//	TCP[0].setup("10.16.9.48", 1111);
    for(int i=0;i<NUM_CLIENTS;i++){
        sendTimer[i] = 0;
    }
}


void Network::update(){

	
	
	for(int i=0;i<NUM_CLIENTS;i++){
        sendTimer[i]--;
		if(clientConnected[i]){
			clientTimeout[i] --;
			if(clientTimeout[i] < 0  ){
				clientConnected[i] = false;
				cout<<"Client "<<i<<" timed out"<<endl;
			}
		}
		
		//Send a message to the client
		if(sendTimer[i] < ofGetElapsedTimeMillis() && sendMessage(i)){
			sendTimer[i] = ofGetElapsedTimeMillis()+50;
			
			//Receive messages that are waiting for us
			string recvstr = TCP[i].receive();
			char * pch;
			pch = strtok ((char*)recvstr.c_str(),";");
			while (pch != NULL)
			{
				clientTimeout[i] = 500;
				clientConnected[i] = true;
				
				receiveMessage(pch, i);
				pch = strtok (NULL, ";");
			}
		}
		
		
		if(!clientConnected[i]) {
			//Try to reconnect now and then
			if(clientReconnect[i] < ofGetElapsedTimeMillis()){				
				cout<<"Trying to reconnect to client "<<i<<endl;
				clientReconnect[i] = ofGetElapsedTimeMillis() + 2000; 

				TCP[i].send("c"+ofToString(i,0));
			}
		}
		
	}
}


void Network::debugDraw(){
    glPushMatrix();
    glTranslated(20, ofGetHeight()-70, 0);
    for(int i=0;i<NUM_CLIENTS;i++){
        ofNoFill();
        ofSetColor(70,70,70);
        ofRect(0, 0, 200, 50);
        
        ofSetColor(150, 150, 150);
        ofDrawBitmapString("Client "+ofToString(i), 5, 15);
        if(clientConnected[i]){
            ofSetColor(0, 255, 0);
            ofDrawBitmapString("Online", 5, 30);
        
        } else {
            ofSetColor(255, 0, 0);
            ofDrawBitmapString("Offline", 5, 30);
        }
        
        glTranslated(220, 0, 0);
    }
    glPopMatrix();
}

void Network::receiveMessage(string message, int client){
//	cout<<"Recv "<<message<<endl;
	if(message.substr(0,1) == "b"){
        analyzer->markNewFrame(client);
	}
	if(message.substr(0,1) == "i"){
		bufferObject[client].bid = atoi(message.substr(1,message.length()-1).c_str());
	}
	if(message.substr(0,1) == "x"){
		bufferObject[client].x = atoi(message.substr(1,message.length()-1).c_str());
	}
	if(message.substr(0,1) == "y"){
		bufferObject[client].y = atoi(message.substr(1,message.length()-1).c_str());
	}
	if(message.substr(0,1) == "w"){
		bufferObject[client].w = atoi(message.substr(1,message.length()-1).c_str());
	}
	if(message.substr(0,1) == "h"){
		bufferObject[client].h = atoi(message.substr(1,message.length()-1).c_str());
        analyzer->addBlobData(bufferObject[client], client);
	}
	
}

bool Network::sendMessage(int i){
	string send;
	send += "t"+ofToString(gui->depthThreshold, 0)+";";
	send += "b"+ofToString(gui->blur, 0)+";";
    send += "T"+ofToString(gui->topCrop-gui->clientOffsetY[i], 0)+";";
    send += "B"+ofToString(gui->bottomCrop+gui->clientOffsetY[i], 0)+";";    
    send += "L"+ofToString(gui->leftCrop[i], 0)+";";
    send += "R"+ofToString(gui->rightCrop[i], 0)+";";    
	return TCP[i].send(send);
}
