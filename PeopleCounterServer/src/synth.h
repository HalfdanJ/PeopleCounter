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
	void say(string msg, string voice, int rate = -1, int pitch = -1);
	
	vector< string > voices;
	vector< string > msgPrefix;
	vector< string > msgAttrib;
	vector< string > msgSuffix;
	
	float lastMsgTime;
	
	//int shortmsgtime;
	//int longmsgtime;
	
	string voice;
	string message;
	
	int maxActivity;
	
	int count;
	int diff;
	
	ofxSpeechSynthesizer    synth;
	
	
	float activityBar;
	//void speechDone();
};


