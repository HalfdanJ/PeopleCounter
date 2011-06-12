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
	gui.addSlider("Blur", blur, 0, 30);

	gui.addTitle("Clients").setNewColumn(true);
    for(int i=0;i<NUM_CLIENTS;i++){
        clientOffset[i] = 320*i;
        gui.addSlider("Client"+ofToString(i)+"Offset", clientOffset[i], 0, 800);
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
