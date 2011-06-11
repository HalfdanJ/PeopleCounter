#include "network.h"

void Network::setup(){
	for(int i=0;i<3;i++){
		oscReceiver.setup(2000+i);
	}

	serverConnected = false;
	timeout = 500;
	myId = -1;
}


void Network::update(){
	if(serverConnected){
		timeout --;
		if(timeout < 0  ){
			serverConnected = false;
			cout<<"Server timed out"<<endl;
		}
	}
	while( oscReceiver.hasWaitingMessages() ){
		timeout = 500;
		
		ofxOscMessage m;
		oscReceiver.getNextMessage( &m );
		
		if ( m.getAddress() == "/connect" ){
			myId = m.getArgAsInt32(0);
			connectToServer();
		}
	}

	
	if(serverConnected){
		//If server is connected, lets send some data
		ofxOscMessage m;
		m.setAddress("/ping");
		oscSender.sendMessage( m );
	}
}


void Network::debugDraw(){
	if(serverConnected){
		ofSetColor(255, 255, 255);
		ofDrawBitmapString("Server connected",640+320, 260);
	} else {
		ofSetColor(255, 50, 50);
		ofDrawBitmapString("Server not connected",640+320, 260);
	}
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("My ID: "+ofToString(myId, 0),640+320, 280);

}


void Network::connectToServer(){
	if(!serverConnected){
		serverConnected = true;
		oscSender.setup("localhost",2000+myId);
	} else {
		cout<<"Server already connected"<<endl;
	}
	
}