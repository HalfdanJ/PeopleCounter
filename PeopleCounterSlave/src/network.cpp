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
			receiveMessage(pch);
			pch = strtok (NULL, ";");
		}
		
		sendMessage(i);
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
//	ofDrawBitmapString("Server ip: "+TCP.getClientIP(TCP.getNumClients()-1),640+320, 290);

}


void Network::receiveMessage(string message){
	cout<<"Recv "<<message<<endl;
	if(message.substr(0,1) == "c"){
		myId = atoi(message.substr(1,1).c_str());
		serverConnected = true;
	}
}

void Network::sendMessage(int i){
	string send;
	send += "b;";
	for(int i=0;i<tracker->blobData.size();i++){
		send += "i"+ofToString(tracker->blobData[i].bid,0)+";";
		send += "x"+ofToString(tracker->blobData[i].x,0)+";";
		send += "y"+ofToString(tracker->blobData[i].y,0)+";";
	}
	TCP.send(i,send);
}


