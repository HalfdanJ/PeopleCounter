#pragma once
#include "defines.h"
#include "ofMain.h"
#include <time.h>

class Timetable {    
public:
    vector<time_t> times;
    
    void setup();
    void populate_times();
    string getNextTime();
};


