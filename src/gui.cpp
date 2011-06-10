#include "gui.h"
#include "ofxSimpleGuiToo.h"

void Gui::setup(Kinect* kinectRef, Tracker * trackerRef){
	kinect = kinectRef;
	tracker = trackerRef;
	
	gui.addTitle("Input");
	
	
	gui.addTitle("Counting").setNewColumn(true);
	gui.addSlider("Height threshold", heightThreshold, 0, 300);
	
	
	
	gui.addTitle("Output").setNewColumn(true);
	
	gui.show();
}

void Gui::update(){
	
}

void Gui::draw(){
	gui.draw();

}
