#include <LedCube3d.h> 

void planeXY(int angle,int value=1);
void waveXZ(int fase, int shift=0, int value=1);

#define SIZE 4 //  кубик из  4 индикаторов
#define COLS (SIZE*SIZE)// размерность кубика 4*4 

byte levelPins [SIZE]= {16,17,18,19};// Аналоговые входы A2,A3,A4,A5. Их подключаем к  этажам кубика
byte colPins [COLS]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};// Цифровые пины D0-D13, аналоговые пины A0,A1

LedCube cube(SIZE, levelPins, colPins);

void setup (){ }

void loop (){
  int i,j,k,l;

  delay(10);

  // столбик, бегущий по диагонали
  for(i=0; i<SIZE; ++i){
    cube.clear_raw();
    for(j=0;j<SIZE;++j){
      cube.point(i,i,j,1);
    }
    cube.show(200);
  }
  
  //вращение плоскости
  for(i=0;i<18;++i){
    cube.clear_raw();
    planeXY(i);
    cube.show(200);
  }
  
  //волна
  for(i=0;i<28;++i){
    cube.clear_raw();
    waveXZ(i);
    cube.show(100);
  }
  
  //заполнение кубика
  cube.clear_raw();
  for(i=0;i<4;++i){
    for(j=0;j<4;++j){
      for(k=0;k<4;++k){
        cube.point(i,j,k);
        cube.show(20);
      }
    }
  }
  cube.show(3000);
}

void planeXY(int angle,int value){
  static int crd[6][4][2]=
                {{{0,3},{1,2},{2,1},{3,0}}, //0
                 {{0,2},{1,2},{2,1},{3,1}}, //1
                 {{0,1},{1,1},{2,2},{3,2}}, //2
                 {{0,0},{1,1},{2,2},{3,3}}, //3
                 {{1,0},{1,1},{2,2},{2,3}}, //4
                 {{2,0},{2,1},{1,2},{1,3}}  //5
                };
  int i,z;
  angle=angle % 6;
  for(z=0;z<SIZE;++z){
    for(i=0;i<SIZE;++i)
        cube.point(crd[angle][i][0],crd[angle][i][1],z,value);
  }
}

void waveXZ(int fase, int shift, int value){
  static int crd[][4][2]=
                {{{3,0},{3,1},{3,2},{2,3}}, //0
                 {{3,0},{2,1},{1,2},{1,3}}, //1
                 {{2,0},{1,1},{0,2},{0,3}}, //2
                 {{1,0},{0,1},{0,2},{1,3}}, //3
                 {{0,0},{1,1},{1,2},{2,3}}, //4
                 {{1,0},{2,1},{2,2},{3,3}}, //5
                 {{2,0},{3,1},{3,2},{3,3}}, //6
                 {{3,0},{3,1},{3,2},{3,3}}  //7
                }; 
  int i,y;
  for(y=0;y<SIZE;++y){
    for(i=0;i<SIZE;++i){
      fase=(fase+shift) % 8;
      cube.point(y,crd[fase][i][1],crd[fase][i][0],value);
    }
  }
}

