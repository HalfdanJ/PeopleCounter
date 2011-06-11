#include "network.h"

void Network::setup(){
	for(int i=0;i<3;i++){
		oscReceiver[i].setup(2000+i);

		clientConnected[i] = false;
		clientTimeout[i] = 500;
		clientReconnect[i] = 0;
		clientPing[i] = 0;
	}
	
	oscSender[0].setup("192.38.71.110", 1111);
}


void Network::update(){
	for(int i=0;i<1;i++){
		if(clientConnected[i]){
			clientTimeout[i] --;
			if(clientTimeout[i] < 0  ){
				clientConnected[i] = false;
				cout<<"Client "<<i<<" timed out"<<endl;
			}
		}
	
		//Receive messages that are waiting for us
		while( oscReceiver[i].hasWaitingMessages() ){
			clientTimeout[i] = 500;
			clientConnected[i] = true;
			
			ofxOscMessage m;
			oscReceiver[i].getNextMessage( &m );
			
			if ( m.getAddress() == "/ping" ){

			}
		}
		
		
		if(clientConnected[i]){
			//Send a ping to te client with settings now and then
			if(clientPing[i] < ofGetElapsedTimeMillis()){
				clientPing[i] = ofGetElapsedTimeMillis() + 1000; 
				
				ofxOscMessage m;
				m.setAddress("/ping");
				oscSender[i].sendMessage( m );
			}
		} else {
			//Try to reconnect now and then
			if(clientReconnect[i] < ofGetElapsedTimeMillis()){
				
				cout<<"Trying to reconnect to client "<<i<<endl;
				clientReconnect[i] = ofGetElapsedTimeMillis() + 2000; 

				ofxOscMessage m;
				m.setAddress("/connect");
				m.addIntArg(i);
				m.addStringArg("10.16.7.247");
				oscSender[i].sendMessage( m );			
			}
		}
		
	}
}


void Network::debugDraw(){
	/*if(serverConnected){
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Server connected",640+320, 260);
	} else {
		ofSetColor(255, 50, 50);
		ofDrawBitmapString("Server not connected",640+320, 260);
	}
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("My ID: "+ofToString(myId, 0),640+320, 280);
*/
}

