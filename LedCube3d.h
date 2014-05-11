/*
    LedCube3D: arduino library for controlling a LED cube
    (c) Sergey Zhumatiy 2014
    MIT License. See accompanying LICENSE file for terms.
*/

#ifndef LedCube3d_h
#define LedCube3d_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class LedCube3D
{
  public:
    LedCube(byte size, byte levelPins[], byte colPins[]);
    ~LedCube();
    
    byte getCols(){ return cols; }
    byte getLevels(){ return levels; }
    byte getNumLights(){ return num; }
    // get/set time interval each level is shown
    int  getShowDelay(){return show_delay;}
    void setShowDelay(int d){show_delay=d;}
    
    void clear();
    void point(int x,int y, int z, int val=1);
    void show(int time);

  private:
    byte cols;
    byte levels;
    byte num;
    int show_delay;
    byte *raw_buffer;
    byte *colPins;
    byte *levelPins;
};

#endif

