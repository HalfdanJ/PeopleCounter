#include "gui.h"
#include "ofxSimpleGuiToo.h"

void Gui::setup(){	
	
	depthThreshold = 100;
	blur = 0;
	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	gui.addTitle("Clients");
	gui.addSlider("Depth threshold", depthThreshold, 0, 255);
	gui.addSlider("Blur", blur, 0, 30);//.setNewColumn(true);

    gui.addTitle("Analyzer").setNewColumn(true);
    for(int i=0;i<NUM_CLIENTS;i++){
        clientOffset[i] = 320*i;
        gui.addSlider("Client"+ofToString(i)+"Offset", clientOffset[i], 0, 800);//.setNewColumn(true);
    }
	
    
	gui.addPage("Network");
	gui.addTitle("Slave 1");
	gui.addSlider("id", slave1id, 0, 10);
	gui.addTitle("Slave 2");
	gui.addSlider("id", slave2id, 0, 10);
	gui.addTitle("Slave 3");
	gui.addSlider("id", slave3id, 0, 10);
	
	//gui.addColorPicker("BG Color", &aColor.r);
	//gui.addComboBox("box1", box1, 12, NULL);
	
	//string titleArray[] = {"Lame", "Alright", "Better", "Best"};
	//gui.addComboBox("box2", box2, 4,  titleArray);
	
	gui.loadFromXML();
	gui.show();
}

void Gui::update(){
	
	//ofBackground(aColor.r * 255, aColor.g * 255.0f, aColor.b * 255.0);
	
	
	slave1id = -1;
	slave2id = -1;
	slave3id = -1;
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
