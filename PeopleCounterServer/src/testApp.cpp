#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	gui = new Gui();
	network = new Network();
	analyzer = new Analyzer();
	
	gui->setup();
	analyzer->setup(gui);
	network->setup(analyzer, gui);

    ofBackground(0,0,0);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){
	gui->update();
	analyzer->update();
	network->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	gui->draw();
	analyzer->debugDraw();
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

