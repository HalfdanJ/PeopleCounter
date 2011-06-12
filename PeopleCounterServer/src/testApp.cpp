#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	gui = new Gui();
	network = new Network();
	analyzer = new Analyzer();
	synth = new Synth();
    filesaver = new Filesaver();
	
	gui->setup();
	analyzer->setup(gui);
    filesaver->setup(analyzer);
	network->setup(analyzer, gui);
	synth->setup(analyzer, gui);

    ofBackground(0,0,0);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){
	gui->update();
    filesaver->update();
	analyzer->update();
	network->update();
	synth->update();
}

//--------------------------------------------------------------
void testApp::draw(){
	gui->draw();
	analyzer->debugDraw();
	network->debugDraw();
    filesaver->debugDraw();
	synth->debugDraw();
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

