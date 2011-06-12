
#include "synth.h"

pascal void speakDoneCallback(SpeechChannel vC, long vRefCnt);
pascal void speakDoneCallback(SpeechChannel vC, long vRefCnt)
{
  //  NSLog(@"Speaking done");
	cout<<"Done"<<endl;
}


void Synth::setup(Analyzer * analyzeRef, Gui * guiRef){
	voices.push_back("Albert");
	voices.push_back("Agnes");
	voices.push_back("Alex");
	//voices.push_back("Bad News");
	//voices.push_back("Bahh");
	//voices.push_back("Bells");
	//voices.push_back("Boing");
	voices.push_back("Bruce");
	//voices.push_back("Bubbles");
	//voices.push_back("Cellos");
	//voices.push_back("Deranged");
	voices.push_back("Fred");
	//voices.push_back("Good News");
	//voices.push_back("Hysterical");
	voices.push_back("Junior");
	voices.push_back("Kathy");
	//voices.push_back("Pipe Organ");
	voices.push_back("Princess");
	voices.push_back("Ralph");
	//voices.push_back("Trinoids");
	voices.push_back("Vicki");
	voices.push_back("Victoria");
	voices.push_back("Whisper");
	//voices.push_back("Zarvox");
	
	msgPrefix.push_back("Hi");
	msgPrefix.push_back("Welcome");
	msgPrefix.push_back("Greetings");
	msgPrefix.push_back("Yo");
	
	
	msgAttrib.push_back("beauty");
	msgAttrib.push_back("human");
	msgAttrib.push_back("strange");
	msgAttrib.push_back("weirdo");
	
	msgSuffix.push_back("enjoy the festival.");
	msgSuffix.push_back("stay safe.");
	msgSuffix.push_back("peace out.");
	msgSuffix.push_back("you have been counted.");
	
	voice = voices.at(1);
	analyzer = analyzeRef;
	gui = guiRef;
	count = 0;
	synth.initSynthesizer();
	lastMsgTime = -10;
	
	activityBar = 0;
	maxActivity = 8;

	
}

void Synth::update(){
	activityBar *= 0.98;
	
	if (analyzer->count > count) {
		
		diff = analyzer->count - count;
		activityBar += diff;
			
		count = analyzer->count;
		// + welcomeMsg[2]
		
		if (activityBar > maxActivity) {
			activityBar = maxActivity;
		}
			
		if (activityBar > 4) {
			say(ofToString(count), voice, 400);
			
		} else if (activityBar > 3.1) {
			say(ofToString(count), voice);
			
		} else if (activityBar > 2) {
			say("Welcome " + ofToString(count), voice);
			
		} else if (activityBar > 1.1) {
			say("Welcome visitor number" + ofToString(count), voice);
			
		} else {			
			voice = voices.at(rand() % voices.size());
			
			string s1 = msgPrefix.at(rand() % msgPrefix.size());
			string s2 = msgAttrib.at(rand() % msgAttrib.size());
			string s3 = msgSuffix.at(rand() % msgSuffix.size());
			message = s1 + " , " + s2 + " , " + s3;
			
			say(message, voice);
		}
		
		
		

		
		
		
		//say("Hi visitor number" + ofToString(count), "Whisper");
		
		lastMsgTime = ofGetElapsedTimef();
		
	}
}


void Synth::say(string msg, string voice, int rate, int pitch){
	
	if (gui->playAudio == true) {
	
		synth.initSynthesizer(voice);
		SetSpeechInfo(synth.speechChannel, soSpeechDoneCallBack,(const void*) speakDoneCallback);
		
		if (rate != -1) {
			SetSpeechRate(synth.speechChannel, IntToFixed(rate));
		}
		
		if (pitch != -1) {
			SetSpeechPitch(synth.speechChannel, IntToFixed(pitch));
		}
		
		synth.speakPhrase(msg);
		
	} else {
		synth.stopSpeaking();
	}

}

