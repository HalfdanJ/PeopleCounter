
#include "synth.h"

int openChannels = 0;

pascal void speakDoneCallback(SpeechChannel vC, long vRefCnt);
pascal void speakDoneCallback(SpeechChannel vC, long vRefCnt)
{
	openChannels -= 1;
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
	//voices.push_back("Whisper");
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
	activityBar = 0;
	maxActivity = 8;
	
	specialMsgTimeDelta = 20;
	lastSpecialMsgTime = ofGetElapsedTimef();
	//say("Ready to count.", voice, 2);
	
}

void Synth::update(){
	activityBar *= 0.98;
	
	
	if (openChannels == 0) {
		
		if (queue.size() > 0) {
			say(queue[0].str, queue[0].voice, queue[0].rate, queue[0].pitch);
			queue.erase(queue.begin());
		}
		
	}
	
	
	if (analyzer->count > count) {
		
		diff = analyzer->count - count;
		activityBar += diff;
			
		count = analyzer->count;
		// + welcomeMsg[2]
		
		if (activityBar > maxActivity) {
			activityBar = maxActivity;
		}
		
		
		if (activityBar > HIGH_ACTIVITY) {
			say(ofToString(count), voice, 400);
					
		} else if (activityBar > LOW_ACTIVITY && queue.size() > 0) {
			addMsg(" and " + ofToString(count), voice, 1);
			
			addMsg(", to roskilde festival!", voice, 0);
			
		} else {			
			voice = voices.at(rand() % voices.size());
			
			string s1 = msgPrefix.at(rand() % msgPrefix.size());
			
			string s3 = msgSuffix.at(rand() % msgSuffix.size());
			
			
			
			addMsg("Welcome, you are guest number " + ofToString(count), voice, 1);
			
			addMsg(", ", voice, 0);
		}
		
		
		if ( (ofGetElapsedTimef() - lastSpecialMsgTime) > specialMsgTimeDelta ) {
			
			if (activityBar > 6) {
				
				cout << "specialmsg";
				lastSpecialMsgTime = ofGetElapsedTimef();
				voice = voices.at(rand() % voices.size());
				addMsg("Give me a break, I'm tired, I hate counting.", voice, 2);
				
			}
			
		}
	}
}





void Synth::addMsg(string str, string voice, int priority, int rate, int pitch){
	
	for (int i=0; i<queue.size(); i++) {
		if (queue[i].priority < priority) {
			queue.erase(queue.begin()+i);
		}
	}
	
	msg newMsg;
	newMsg.str = str;
	newMsg.voice = voice;
	newMsg.priority = priority;
	newMsg.rate = rate;
	newMsg.pitch = pitch;
	
	queue.push_back(newMsg);
	
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
		
		openChannels += 1;
		synth.speakPhrase(msg);
		
	} else {
		synth.stopSpeaking();
	}

}

void Synth::debugDraw(){
	glPushMatrix();
	glTranslated(ofGetWidth()-220, ofGetHeight()-70, 0);
	ofNoFill();
	ofSetColor(70,70,70);
	ofRect(0, 0, 200, 50);

	ofFill();
	ofSetColor(100, 100, 100);;
	if(activityBar > LOW_ACTIVITY){
		ofSetColor(0, 255, 0);
	} if (activityBar > NORMAL_ACTIVITY) {
		ofSetColor(255, 255, 0);
	} if (activityBar > HIGH_ACTIVITY) {
		ofSetColor(255, 0, 0);
	}
	float ac = ofClamp(200.0*activityBar / 8.0,0,200);
	ofRect(0, 0, ac, 50);
	
	glPopMatrix();
}