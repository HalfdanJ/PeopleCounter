//
//  timetable.cpp
//  PeopleCounterServer
//
//  Created by Jonas Jongejan on 6/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "timetable.h"

void Timetable::setup(){
    populate_times();
}

string Timetable::getNextTime(){
    int i =0;
	time_t epoch;
    struct tm * timeinfo;
    char buffer[10];

	time(&epoch);
    timeinfo = localtime ( &epoch );
    
    time_t bestMatch = -1;
    for(int i=0;i<times.size();i++){
        if(times[i] > epoch && (bestMatch == -1 || times[i] < bestMatch)){
            bestMatch = times[i];
        }
    }
    
    if(bestMatch == -1){
        return " - ";
    } else {
        timeinfo = localtime ( &bestMatch );
        strftime (buffer,10,"%H:%M",timeinfo);  
        return buffer;
    }
}

void Timetable::populate_times() {
	int t = 0;
	int d = 0;
	int i = 0;	
	int fridayptr = 0, saturdayptr = 0; 
	// monday through thursday can be calculated
	for (d=0; d<4; d++) {
		// half-hour intervals
		for (i=0;i<21; i++) {
			times.push_back(1309167600 + i*1800 + d*86400);
		}
		
		// full hour intervals
		for (i = 1; i<5; i++) {
			times.push_back(1309167600 + 20*1800 + i*3600 + d*86400);
		}
	}
    
    
	// thursday has some more times
	times.push_back(1309167600 + 20*1800 + 5*3600 + 3*86400); // 00:40
	times.push_back(1309482840); // 01:14
	times.push_back(1309486200); // 02:10
    
	// friday
	d = 4;
	fridayptr = t;
	// half-hour intervals
	for (i=0;i<21; i++) {
		times.push_back(1309167600 + i*1800 + d*86400);
	}
    
	// full hour intervals
	for (i = 1; i<5; i++) {
		times.push_back(1309167600 + 20*1800 + i*3600 + d*86400);
	}
    
	times.push_back(1309167600 + 20*1800 + 5*3600 + d*86400); // 00:40
	times.push_back(1309569240); // 01:14
	times.push_back(1309572600); // 02:10
	times.push_back(1309576500); // 03:15
	times.push_back(1309576500 + 3600); // 04:15
    
	// saturday == friday
	saturdayptr = t;
	for (;fridayptr<saturdayptr; fridayptr++) {
		times.push_back(times[fridayptr] + 86400);
	}
    
    
	// sunday
	d = 6;
	// half-hour intervals
	for (i=0;i<21; i++) {
		times.push_back(1309167600 + i*1800 + d*86400);
	}
    
	// full hour intervals
	for (i = 1; i<5; i++) {
		times.push_back(1309167600 + 20*1800 + i*3600 + d*86400);
	}
    
	times.push_back(times[times.size()-1]+1800); // 00:10   (23:40 + 30 minutes)
    times.push_back(times[times.size()-1]+1800); // 00:40
    times.push_back(times[times.size()-1]+1800); // 01:10
    times.push_back(times[times.size()-1]+1800); // 01:40
    times.push_back(times[times.size()-1]+1200); // 02:00
    times.push_back(times[times.size()-1]+900);  // 02:15
    times.push_back(times[times.size()-1]+1080); // 02:33
    times.push_back(times[times.size()-1]+2220); // 03:10
    times.push_back(times[times.size()-1]+3600); // 04:10
    times.push_back(times[times.size()-1]+960);  // 04:26
    times.push_back(times[times.size()-1]+2940);  // 05:15
    
	d=7;
	// half-hour intervals
	for (i=0;i<10; i++) {
		times.push_back(1309167600 + i*1800 + d*86400);
	}
    
	return;
}
