#include "network.h"

void Network::setup(Analyzer * analyzeRef){
	analyzer = analyzeRef;
	
	for(int i=0;i<3;i++){
		clientConnected[i] = false;
		clientTimeout[i] = 500;
		clientReconnect[i] = 0;
		clientPing[i] = 0;
	}
	
	//TCP[0].setup("192.38.71.110", 1111);
	TCP[0].setup("localhost", 1111);
	//TCP[0].setup("10.16.9.48", 1111);
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
	
		//Send a message to the client
		if(sendMessage(i)){
			//Receive messages that are waiting for us
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
}

void Network::receiveMessage(string message, int client){
	cout<<"Recv "<<message<<endl;
	if(message.substr(0,1) == "b"){
		analyzer->blobData[client].clear();
	}
	if(message.substr(0,1) == "i"){
		bufferObject.bid = atoi(message.substr(1,message.length()-1).c_str());
	}
	if(message.substr(0,1) == "x"){
		bufferObject.x = atoi(message.substr(1,message.length()-1).c_str());
	}
	if(message.substr(0,1) == "y"){
		bufferObject.y = atoi(message.substr(1,message.length()-1).c_str());
		analyzer->blobData[client].push_back(bufferObject);
	}
	
}

bool Network::sendMessage(int i){
	TCP[i].send("ping");
}
