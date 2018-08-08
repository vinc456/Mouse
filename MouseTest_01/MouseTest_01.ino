/*

  Mouse Eye X Y reader
  Written by Joel Murphy for Rachel's Electronics
  Released into the wild. Fall, 2010

*/
#include "MouseDefinitions.h"
#include <Mouse.h>
#include <MouseEye.h>
MouseEye eye(ADNS_SCK, ADNS_SDIO);   // SCK on pin 9, SDIO on pin 8
boolean stopped = false;

boolean hid = false;

void setup() {
//  Serial.begin(115200);
  delay(1000);
//  Serial.println("Mouse Test 01");
  setPins();
  
  hid = digitalRead(HID_SELECT);
  if(hid){
    Mouse.begin();
//    Serial.println("hid");
  } else {
    Serial.begin(115200);
    Serial.println("not hid");
    Serial.println("Mouse Test 01");
  }
}


void loop() {
  
  eye.getMouseEyeDelta();      // update deltaX and deltaY variables
  if (eye.deltaX != 0 || eye.deltaY != 0) { //when mouse is moving
    if(hid){
      Mouse.move(eye.deltaX,eye.deltaY,0);
    } else {
      Serial.print(eye.deltaX, DEC);               //when mouse is moving
      Serial.print("\t");                          //pirnt the delta X and Y
      Serial.println(eye.deltaY, DEC);
    }
  }


  checkButtons();
  if(!hid){ eventSerial(); }

  delay(10);
}





void setPins() {
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(HID_SELECT, INPUT);
  pinMode(WHEEL_A, INPUT);
  pinMode(WHEEL_B, INPUT);
}

