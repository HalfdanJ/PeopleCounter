#include "synth.h"

void Synth::setup(Analyzer * analyzeRef, Gui * guiRef){
	
	analyzer = analyzeRef;
	gui = guiRef;
	
	count = 0;
	
	synth.initSynthesizer();
	
	string messages[] = {"Welcome to Roskilde Festival", 
		"Hi jerk", "Hi you, remember me?", 
		"I love you!", 
		"Didn't think I would see you again."};
	
	
	voices = synth.getListOfVoices();
	
	if(voices.size() > 0)
    {
        std::map<std::string, int>::iterator iter;
        for(iter = voices.begin(); iter != voices.end(); ++iter)
        {
            std::cout << iter->second << ", " << iter->first << std::endl;
        }
    }
	
	analyzer->count += 1;
	
}

void Synth::update(){
	
	if (analyzer->count > count) {
		
		diff = analyzer->count - count;
		count = analyzer->count;
		
		say("hi visitor number" + ofToString(count), "Whisper");

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
