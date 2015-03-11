#include <math.h>
#include <Wire.h>

// Settings
#define OVERTEMP                340
// Pin assignments
#define DPIN_RLED_SW            2
#define DPIN_GLED               5
#define DPIN_PWR                8
#define DPIN_DRV_MODE           9
#define DPIN_DRV_EN             10
#define APIN_TEMP               0
#define APIN_CHARGE             3

#define MODE_OFF                0
#define MODE_ON                 1
#define MODE_DAZ                2

struct DazzleData{
  int bgt;
  unsigned long lastTime;
  unsigned long interval;
  byte lastMode;
};

DazzleData dd;
unsigned long lastClickTime = 0;
unsigned long lastHoldTime = 0;
byte mode = 0;
boolean oldBut = false;

void setup(){
  pinMode(DPIN_PWR,      INPUT);
  digitalWrite(DPIN_PWR, LOW);
  
  // Initialize GPIO
  pinMode(DPIN_RLED_SW,  INPUT);
  pinMode(DPIN_GLED,     OUTPUT);
  pinMode(DPIN_DRV_MODE, OUTPUT);
  pinMode(DPIN_DRV_EN,   OUTPUT);
  digitalWrite(DPIN_DRV_MODE, LOW);
  digitalWrite(DPIN_DRV_EN,   LOW);
  
  // Initialize serial busses
  Serial.begin(9600);
  Wire.begin();
  
  mode = MODE_OFF;
}

void loop(){
  static unsigned long lastTempTime;
  unsigned long time = millis();
  
  checkBattery(&time);
  checkTemp(&time, &lastTempTime);
  fixPin();
  
  int btnEvent = checkButtonEvent();
  switch(btnEvent){
    case 0:
      //do nothing
      break;
    case 1:
      onClick();
      break;
    case 2:
      onHold();
      break;
    case 3:
      onReleased();
      break;
    default:
      break;
  }
}


