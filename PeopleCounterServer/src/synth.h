#pragma once

#include "ofMain.h"
#include "gui.h"
#include "analyzer.h"
#include "ofxSpeech.h"
#include "defines.h"

struct msg {
	string str;
	int priority;
	string voice;
	int rate;
	int pitch;
};

#define LOW_ACTIVITY 0.9
#define NORMAL_ACTIVITY 2
#define HIGH_ACTIVITY 4

class Synth {
public:
	
	Analyzer * analyzer;
	Gui * gui;
	
	void setup(Analyzer * analyzer, Gui * gui);
	void update();
	void debugDraw();
	
	void addMsg(string msg, string voice, int priority = 0, int rate = -1, int pitch = -1);
	void say(string msg, string voice, int rate = -1, int pitch = -1);
	
	vector< string > voices;
	vector< string > msgPrefix;
	vector< string > msgAttrib;
	vector< string > msgSuffix;
	
	vector< msg > queue;
	
	float lastSpecialMsgTime;
	
	float specialMsgTimeDelta;
	
	string voice;
	string message;
	
	int maxActivity;
	
	int count;
	int diff;
		
	ofxSpeechSynthesizer    synth;
	
	
	float activityBar;
	//void speechDone();
};


