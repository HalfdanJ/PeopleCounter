#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#include "kinect.h"
#include "tracker.h"
#include "gui.h"



class PeopleCounterApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	
	
	Kinect * kinect;
	Tracker * tracker;
	Gui * gui;
	
};

void PeopleCounterApp::setup()
{
	kinect = new Kinect();
	tracker = new Tracker();
	gui = new Gui();
	
	kinect->setup();
	tracker->setup(kinect);
	gui->setup(kinect, tracker);
	
}

void PeopleCounterApp::mouseDown( MouseEvent event )
{
}

void PeopleCounterApp::update()
{
	kinect->update();
	tracker->update();
	gui->update();
}

void PeopleCounterApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
	
	gui->draw();
	
	tracker->debugDraw();
	kinect->debugDraw();
}

void PeopleCounterApp::keyDown( KeyEvent event){
	gui->keyPressed(event.getCode());
}


CINDER_APP_BASIC( PeopleCounterApp, RendererGl )
