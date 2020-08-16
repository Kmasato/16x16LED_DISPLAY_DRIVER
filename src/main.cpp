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

void setLEDbyByte(byte,int);
void setPoint16x16(int, int, bool);

void setup() {
  Serial.begin(115200);
  mx.begin();
}

void loop() {

  byte framePacket[32]={};

  if(Serial.available()){
    mx.clear();
    for(int i = 0; i < 32; i++){
      framePacket[i] = Serial.read();
    }
  }

  for(int i=0; i<32; i++){
     setLEDbyByte(framePacket[i], i);
  }
  
}

void setLEDbyByte(byte data, int index){
  for(int i=0; i < 8; i++){
    if(((data >> (7-i))&0x01) == 0x01){
      if(index%2 == 1){
        setPoint16x16(i+8, (int)index/2, true);
      }
      else{
        setPoint16x16(i, (int)index/2, true);
      }
    }
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