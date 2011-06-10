#include "gui.h"

void Gui::setup(Kinect* kinectRef, Tracker * trackerRef){
	/*kinect = kinectRef;
	tracker = trackerRef;

	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	// for demonstrating adding any drawable object (that extends ofBaseDraw);
	vidGrabber.initGrabber(320, 240);	
	videoInverted 	= new unsigned char[int(vidGrabber.getWidth() * vidGrabber.getHeight() * 3)];
	videoTexture.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
	
	gui.addTitle("Input");
	gui.addContent("Camera feed", vidGrabber);
	
	gui.addTitle("Counting").setNewColumn(true);
	gui.addSlider("Height threshold", heightThreshold, 0, 300);
	gui.addContent("Inverted", videoTexture);
	
	gui.addTitle("Output").setNewColumn(true);
	
	gui.addPage("Status");
	
	gui.loadFromXML();
	
	gui.show();*/
}

void Gui::update(){
	/*// from ofVideoGrabber example (
	vidGrabber.update();
	if(vidGrabber.isFrameNew()){
		int totalPixels = vidGrabber.getWidth() * vidGrabber.getHeight() * 3;
		unsigned char * pixels = vidGrabber.getPixels();
		for(int i = 0; i < totalPixels; i++) videoInverted[i] = 255 - pixels[i];
		videoTexture.loadData(videoInverted, vidGrabber.getWidth(), vidGrabber.getHeight(), GL_RGB);
	}	
	 */
}

void Gui::draw(){
	//gui.draw();
}

void Gui::keyPressed (int key){ 
	/*if(key>='0' && key<='9') {
		gui.setPage(key - '0');
		
		synth->say(ofToString(key));
		
		gui.show();
	} else {
		switch(key) {
			case ' ': gui.toggleDraw(); break;
			case '[': gui.prevPage(); break;
			case ']': gui.nextPage(); break;
			case 'p': gui.nextPageWithBlank(); break;
		}
	}
	 */
}
