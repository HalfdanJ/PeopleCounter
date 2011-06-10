#include "gui.h"
#include "ofxSimpleGuiToo.h"

int		height;

void Gui::setup(Kinect* kinectRef, Tracker * trackerRef){
	kinect = kinectRef;
	tracker = trackerRef;
	
	gui.addTitle("A group");
	
	
	gui.addSlider("Height threshold:", height, 0, 300); 
	
	gui.show();

}

void Gui::update(){
	
}

void Gui::draw(){
	gui.draw();

}
