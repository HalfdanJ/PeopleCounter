#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	kinect = new Kinect();
	tracker = new Tracker();
	network = new Network();
	
	kinect->setup();
	tracker->setup(kinect);
	network->setup(tracker);	
	
	ofBackground(100, 100, 100);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){
	kinect->update();
	tracker->update();
	network->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	tracker->debugDraw();
	kinect->debugDraw();
	network->debugDraw();
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Framerate: "+ofToString(ofGetFrameRate(), 1), 650, 260);
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

