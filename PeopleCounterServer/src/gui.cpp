#include "gui.h"
#include "ofxSimpleGuiToo.h"

ofVideoGrabber		vidGrabber;
unsigned char * 	videoInverted;
ofTexture			videoTexture;

void Gui::setup(){	
	
	depthThreshold = 100;
	blur = 0;
	
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	// for demonstrating adding any drawable object (that extends ofBaseDraw);	
	vidGrabber.initGrabber(320, 240);	
	videoInverted 	= new unsigned char[int(vidGrabber.getWidth() * vidGrabber.getHeight() * 3)];
	videoTexture.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
	
	gui.addTitle("Analyzer");
	gui.addSlider("Depth threshold", depthThreshold, 0, 255);
	gui.addSlider("Blur", blur, 0, 30);
	
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
	
	ofBackground(aColor.r * 255, aColor.g * 255.0f, aColor.b * 255.0);
	
	
	slave1id = -1;
	slave2id = -1;
	slave3id = -1;
	
	// from ofVideoGrabber example (
	vidGrabber.update();
	if(vidGrabber.isFrameNew()){
		int totalPixels = vidGrabber.getWidth() * vidGrabber.getHeight() * 3;
		unsigned char * pixels = vidGrabber.getPixels();
		for(int i = 0; i < totalPixels; i++) videoInverted[i] = 255 - pixels[i];
		videoTexture.loadData(videoInverted, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
	}
	
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
