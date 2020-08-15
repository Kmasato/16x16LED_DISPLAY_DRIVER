#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 5

#define ROW_SIZE 16
#define COLUMN_SIZE 16
#define NUM 3

MD_Parola parola = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

short moji[NUM][COLUMN_SIZE][ROW_SIZE] = {{ 
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
 {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
 {0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
 {0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
 {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0}},

 {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0},
 {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0},
 {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
 {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},

 {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
 {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
 {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
 {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} 
 }
 };

void setPoint16x16(int, int, bool);

void setup() {
  mx.begin();
}

void loop() {

  for(int count=0; count < NUM; count++){
    for(int i=0; i < COLUMN_SIZE; i++){
      for(int j=0; j< ROW_SIZE; j++){
        if(moji[count][i][j] == 1)
          setPoint16x16(j, i, true);
      }
    }
    delay(300);
    mx.clear();
  }
}

void setPoint16x16(int x, int y, bool state){
  if(0 <= y && y < 8){
    mx.setPoint(7-y, x, state);
  }
  if(8 <= y && y < 16){
    mx.setPoint(15-y, x+16, state);
  }
}