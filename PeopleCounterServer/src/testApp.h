#pragma once

#include "ofMain.h"
#include "analyzer.h"
#include "gui.h"
#include "network.h"
#include "defines.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
	Gui * gui;
	Network * network;
	Analyzer * analyzer;

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

};