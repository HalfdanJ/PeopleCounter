#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	gui = new Gui();
	network = new Network();
	
	gui->setup();
	network->setup();

}

//--------------------------------------------------------------
void testApp::update(){
	gui->update();
	network->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	gui->draw();
	network->debugDraw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	gui->keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

