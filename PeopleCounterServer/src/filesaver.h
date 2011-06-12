#pragma once
#include "defines.h"
#include "analyzer.h"
#include "ofMain.h"

class Filesaver {
public:
    Analyzer * analyzer;
    
    void setup(Analyzer * analyzer);
    void update();
    void debugDraw();
};