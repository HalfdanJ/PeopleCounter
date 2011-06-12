#include "filesaver.h"

void Filesaver::setup(Analyzer * analyzerRef){
    analyzer = analyzerRef;

    FILE * pFile;  
    int numLines =0;
    pFile = fopen (ofToDataPath("data.txt").c_str(),"r");  
    
    if (pFile!=NULL)  
    {  
        while(!feof(pFile)) {
            numLines += getc(pFile) == '\n';
        }
        fclose (pFile);  
    }
	analyzer->count = numLines;
	
	analyzer->count = 56101;
	
}

void Filesaver::update(){
    time_t rawtime;  
    struct tm * timeinfo;  
    time ( &rawtime );  
    timeinfo = localtime ( &rawtime );  
    

    if(analyzer->addedCount > 0){
        FILE * pFile;  
        pFile = fopen (ofToDataPath("data.txt").c_str(),"a+");  
        if (pFile!=NULL)  
        {  
            for(int i=0;i<analyzer->addedCount;i++){                
                blob_data * data = &analyzer->combinedBlobs[analyzer->combinedBlobs.size() - i - 1];
                string str = ofToString(rawtime,0)+";\n";
                fputs (str.c_str(),pFile);  
            }  
            fclose (pFile);  
        }
    }

}

void Filesaver::debugDraw(){
    
}