#include "synth.h"


string welcomeMsg[4] = { " Hi jerk" , " I love you!", " Didn't think I would see you here", " Welcome to Roskilde Festival" };


void Synth::setup(Analyzer * analyzeRef, Gui * guiRef){
	
	analyzer = analyzeRef;
	gui = guiRef;
	
	count = 0;
	
	synth.initSynthesizer();
	
	voices = synth.getListOfVoices();
	
	lastMsgTime = -10;
	
	if(voices.size() > 0)
    {
        std::map<std::string, int>::iterator iter;
        for(iter = voices.begin(); iter != voices.end(); ++iter)
        {
            std::cout << iter->second << ", " << iter->first << std::endl;
        }
    }
	
}

void Synth::update(){
	
	if (analyzer->count > count) {
		
		diff = analyzer->count - count;
		
		if (ofGetElapsedTimef() - lastMsgTime > 3) {
			// wait for old msg to finish
			
			count = analyzer->count;
			// + welcomeMsg[2]
			
			say("Hi visitor number" + ofToString(count), "Whisper");
			
			lastMsgTime = ofGetElapsedTimef();
		}
		
		

	}
}


void Synth::say(string msg, string voice){
	
	if (gui->playAudio == true) {
	
		if (synth.getCurrentVoice() != voice) {
			synth.initSynthesizer(voice);
		}
	
		synth.speakPhrase(msg);
		
	} else {
		synth.stopSpeaking();
	}

}
