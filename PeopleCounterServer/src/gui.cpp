#include "gui.h"
#include "ofxSimpleGuiToo.h"

void Gui::setup(){
	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	// set defaults
	depthThreshold = 100;
	blur = 0;
	playAudio = 1;
	addPerson = 1;
	
	gui.addTitle("Analyzer");
	gui.addSlider("Depth threshold", depthThreshold, 0, 255);
	gui.addSlider("Blur", blur, 0, 30);//.setNewColumn(true);
    gui.addSlider("Merge distance", analyzerMergeDist,0,100);
    gui.addSlider("Blob min size", minBlobSize,0,640*480);
    gui.addSlider("Blob max size", maxBlobSize,0,640*480);
    
	gui.addTitle("Clients").setNewColumn(true);
    for(int i=0;i<NUM_CLIENTS;i++){
        clientOffsetX[i] = 320*i;
        gui.addSlider("Client"+ofToString(i)+"OffsetX", clientOffsetX[i], 0, 800);//.setNewColumn(true);
        clientOffsetY[i] = 320*i;
        gui.addSlider("Client"+ofToString(i)+"OffsetY", clientOffsetY[i], -100, 100);//.setNewColumn(true);

    }

    gui.addPage("Cropping");
    topCrop = 0;
    gui.addSlider("ClientTopCrop", topCrop, 0, 640);//.setNewColumn(true);
    bottomCrop = 0;
    gui.addSlider("ClientBottomCrop", bottomCrop, 0, 640);//.setNewColumn(true);

    for(int i=0;i<NUM_CLIENTS;i++){
        leftCrop[i] = 0;
        gui.addSlider("Client"+ofToString(i)+"LeftCrop", leftCrop[i], 0, 640).setNewColumn(true);
        rightCrop[i] = 0;
        gui.addSlider("Client"+ofToString(i)+"RightCrop", rightCrop[i], 0, 640);//.setNewColumn(true);
    }
	
	gui.addTitle("Speech synth").setNewColumn(true);
	gui.addToggle("Play audio", playAudio);
	
	gui.addButton("Add person", addPerson);
	
	gui.loadFromXML();
	gui.show();
}

void Gui::update(){
}

void Gui::draw(){
	gui.draw();
}

void Gui::keyPressed (int key){ 
	if(key>='0' && key<='9') {
		gui.setPage(key - '0');
		gui.show();
	} else {
		switch(key) {
			case ' ': gui.toggleDraw(); break;
			case '[': gui.prevPage(); break;
			case ']': gui.nextPage(); break;
			case 'p': gui.nextPageWithBlank(); break;
		}
	}
}
