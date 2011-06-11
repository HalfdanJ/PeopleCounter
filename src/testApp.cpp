#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	kinect = new Kinect();
	tracker = new Tracker();
	
	kinect->setup();
	tracker->setup(kinect);
	
}

//--------------------------------------------------------------
void testApp::update(){
	kinect->update();
	tracker->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	tracker->debugDraw();
	kinect->debugDraw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
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

