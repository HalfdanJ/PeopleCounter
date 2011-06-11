#include "network.h"

void Network::setup(Tracker* trackerRef){
	tracker = trackerRef;
	
	TCP.setup(1111);

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
	
	
	for(int i = 0; i < TCP.getNumClients(); i++){		
		string recvstr = TCP.receive(i);
		char * pch;
		pch = strtok ((char*)recvstr.c_str(),";");
		while (pch != NULL)
		{
			timeout = 500;
			
			printf ("%s\n",pch);
			
			receiveMessage(pch);
			pch = strtok (NULL, ";");
		}
	}
	


	if(serverConnected){
		//If server is connected, lets send some data
		string send = "ping";
		for(int i = 0; i < TCP.getNumClients(); i++){
		TCP.send(i,send);
		}
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
	ofDrawBitmapString("My id: "+ofToString(myId, 0),640+320, 280);
	ofDrawBitmapString("Server ip: "+serverIp,640+320, 290);

}

/*
void Network::connectToServer(){
	if(!serverConnected){
		serverConnected = true;
//		oscSender.setup(serverIp,2000+myId);
	} else {
		cout<<"Server already connected"<<endl;
	}
	
}*/

void Network::receiveMessage(string message){
	cout<<"Recv "<<message<<endl;
	if(message.substr(0,1) == "c"){
		myId = atoi(message.substr(1,1).c_str());
		serverConnected = true;
	}
}


