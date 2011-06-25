#include "filesaver.h"

void Filesaver::setup(Analyzer * analyzerRef){
    analyzer = analyzerRef;
    char line[13];

    FILE * pFile;  
    int numLines =0;
    pFile = fopen (ofToDataPath("data.txt").c_str(),"r");  
    
    if (pFile!=NULL)  
    {  
        /*while(!feof(pFile)) {
            numLines += getc(pFile) == '\n';
        }
        */
        int rawtime = currentTime();
        while( fgets(line, sizeof(line), pFile) != NULL ) {
            /* Get each line from the infile */
            numLines++;
            /* print the line number and data */
            printf("Line %d: %s", numLines, line);  
            
            string time = string(line).substr(0,10);
            int iTime;;
            sscanf(time.c_str(), "%d", &iTime);
            if(fabs(rawtime - iTime) < 60*60){
                hourVector.push_back(iTime);
            }
        }
        
        fclose (pFile);  
    }
	analyzer->count = numLines;
	
//	analyzer->count = 56101;
	
}

int Filesaver::currentTime(){
    time_t rawtime;  
    struct tm * timeinfo;  
    time ( &rawtime );   
    timeinfo = localtime ( &rawtime );  
    return rawtime;
}

void Filesaver::update(){
    cout<<countOfLastHour()<<endl;
    
    int rawtime = currentTime();
    

    if(analyzer->addedCount > 0){
        FILE * pFile;  
        pFile = fopen (ofToDataPath("data.txt").c_str(),"a+");  
        if (pFile!=NULL)  
        {  
            for(int i=0;i<analyzer->addedCount;i++){                
                blob_data * data = &analyzer->combinedBlobs[analyzer->combinedBlobs.size() - i - 1];
                string str = ofToString(rawtime,0)+";\n";
                fputs (str.c_str(),pFile); 
                
                hourVector.push_back(rawtime);
            }  
            fclose (pFile);  
        }
    }

}

int Filesaver::countOfLastHour(){
    int rawtime = currentTime();

    for(int i=0;i<hourVector.size();i++){
        if(fabs(rawtime - hourVector[i]) > 60*60){
            hourVector.erase(hourVector.begin()+i);
        }
    }
    return hourVector.size(); 
}

void Filesaver::debugDraw(){
    
}