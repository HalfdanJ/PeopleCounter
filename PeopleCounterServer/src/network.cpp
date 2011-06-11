#include "network.h"

void Network::setup(){
	for(int i=0;i<3;i++){
		clientConnected[i] = false;
		clientTimeout[i] = 500;
		clientReconnect[i] = 0;
		clientPing[i] = 0;
	}
	
	//TCP[0].setup("192.38.71.110", 1111);
	TCP[0].setup("localhost", 1111);
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
		//while( oscReceiver[i].hasWaitingMessages() ){
			
			string recvstr = TCP[i].receive();
			char * pch;
			pch = strtok ((char*)recvstr.c_str(),";");
			while (pch != NULL)
			{
				clientTimeout[i] = 500;
				clientConnected[i] = true;

				printf ("%s\n",pch);
				
				receiveMessage(pch, i);
				pch = strtok (NULL, ";");
			}
			
	//	}
		
		
		if(clientConnected[i]){
			//Send a ping to te client with settings now and then
			if(clientPing[i] < ofGetElapsedTimeMillis()){
				clientPing[i] = ofGetElapsedTimeMillis() + 1000; 
				
				/*ofxOscMessage m;
				m.setAddress("/ping");
				oscSender[i].sendMessage( m );*/
				TCP[i].send("ping");
			}
		} else {
			//Try to reconnect now and then
			if(clientReconnect[i] < ofGetElapsedTimeMillis()){
				
				cout<<"Trying to reconnect to client "<<i<<endl;
				clientReconnect[i] = ofGetElapsedTimeMillis() + 2000; 

				TCP[i].send("c"+ofToString(5,0));
			}
		}
		
	}
}


void Network::debugDraw(){
}

void Network::receiveMessage(string message, int client){
	cout<<"Recv "<<message<<endl;
/*	if(message.substr(0,1) == "c"){
		myId = atoi(message.substr(1,1).c_str());
		serverConnected = true;
	}*/
}
