/*
    LedCube3D: arduino library for controlling a LED cube
    (c) Sergey Zhumatiy 2014
    MIT License. See accompanying LICENSE file for terms.
*/

#include "LedCube3D.h"

#define RAW_DELAY 5

// size, level pins, field pins
LedCube3D::LedCube3D(byte size, byte lp[], byte cp[]) :
    levels(size), cols(size*size), num(pow(size, 3)),
    show_delay(RAW_DELAY)
{
//    randomSeed(analogRead(0));

    // allocate memory for dynamic members
    //buffer = (byte**) malloc(levels * sizeof(byte *));
    raw_buffer = (byte*) malloc(cols);
    levelPins = (byte*) malloc(levels);
    colPins = (byte*) malloc(cols);
    enable_vector=(byte *)malloc(cols);

    // configure level pins and finish allocation for buffer
    for (byte i = 0; i < levels; i++)
    {
        levelPins[i] = lp[i];
        pinMode(levelPins[i], OUTPUT);

        //buffer[i] = (byte*) malloc(cols * sizeof(byte));
    }

    // configure column pins
    for (byte i = 0; i < cols; i++)
    {
        colPins[i] = cp[i];
        pinMode(colPins[i], OUTPUT);
    }

    clear();
}

LedCube3D::~LedCube3D()
{
    free(raw_buffer);
    free(levelPins);
    free(colPins);
    free(enable_vector);
}

// clear all points (set off)
void LedCube3D::clear(){
  for(int i=0;i<(cols);++i)
    raw_buffer[i]=0;
}

// set or reset any 3d-point
// if val=0 - turn it off, if not 0 - turn on.
void LedCube3D::point(int x,int y, int z, int val){
  if(val)
    raw_buffer[z*levels+y] |= 1<<x;
  else
    raw_buffer[z*levels+y] &= 1<<x;
}

// show your cube for 'time' microseconds
void LedCube3D::show(int time){
  int i,z,y,x,cur,n,t=time;

  // turn off all leds
  for(i=0;i<levels;++i)
    digitalWrite(levelPins[i],LOW);
  for(i=0;i<cols;++i)
    digitalWrite(colPins[i],HIGH);

  while(t>0){
    cur=0;
    for(z=0; z<levels; ++z){
      n=0;
      for(y=0; y<levels; ++y){
        for(x=0; x<levels; ++x){
          enable_vector[n]=
            (raw_buffer[cur] & (1<<x)) ? LOW : HIGH;
          ++n;
        }
        ++cur;
      }
      digitalWrite(levelPins[z],HIGH);
      // show level plane!
      for(i=0;i<cols;++i){
        digitalWrite(colPins[i],enable_vector[i]);
      }
      delay(RAW_DELAY);
      digitalWrite(levelPins[z],LOW);
      t=t-RAW_DELAY;
    }
  }
}
