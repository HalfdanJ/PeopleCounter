#include "peopleCounterServerApp.h"

//--------------------------------------------------------------
void peopleCounterServerApp::setup(){
	gui = new Gui();
	network = new Network();
	
	gui->setup();
	network->setup();

}

//--------------------------------------------------------------
void peopleCounterServerApp::update(){
	gui->update();
	network->update();
}

//--------------------------------------------------------------
void peopleCounterServerApp::draw(){
	gui->draw();
	network->debugDraw();
}

//--------------------------------------------------------------
void peopleCounterServerApp::keyPressed(int key){

}

//--------------------------------------------------------------
void peopleCounterServerApp::keyReleased(int key){

}

//--------------------------------------------------------------
void peopleCounterServerApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void peopleCounterServerApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void peopleCounterServerApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void peopleCounterServerApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void peopleCounterServerApp::windowResized(int w, int h){

}

