#pragma once

#include "ofMain.h"
#include "gui.h"
#include "analyzer.h"
#include "ofxSpeech.h"
#include "defines.h"

class Synth {
public:
	
	Analyzer * analyzer;
	Gui * gui;
	
	void setup(Analyzer * analyzer, Gui * gui);
	void update();
	void say(string msg, string voice);
	
	map< string, int > voices;
	
	
	vector< string > messages;
	
	int count;
	int diff;
	
	ofxSpeechSynthesizer    synth;
};


