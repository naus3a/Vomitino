void checkBattery(unsigned long * time){
  // Check the state of the charge controller
  int chargeState = analogRead(APIN_CHARGE);
  if (chargeState < 128)  // Low - charging
  {
    digitalWrite(DPIN_GLED, ((*time)&0x0100)?LOW:HIGH);
  }
  else if (chargeState > 768) // High - charged
  {
    digitalWrite(DPIN_GLED, HIGH);
  }
  else // Hi-Z - shutdown
  {
    digitalWrite(DPIN_GLED, LOW);    
  }
}

void checkTemp(unsigned long * time, unsigned long * lTime){
  if(time-lTime>1000){
    lTime =  time;
    int temp = analogRead(APIN_TEMP);
    if(temp>OVERTEMP && mode!=MODE_OFF){
      for (int i = 0; i < 6; i++)
      {
        digitalWrite(DPIN_DRV_MODE, LOW);
        delay(100);
        digitalWrite(DPIN_DRV_MODE, HIGH);
        delay(100);
      }
      turnOff();
    }
  }
}

void fixPin(){
  pinMode(DPIN_RLED_SW, OUTPUT);
  pinMode(DPIN_RLED_SW, INPUT);
}

boolean isButtonDown(){
  return digitalRead(DPIN_RLED_SW);
}

int checkButtonEvent(){
  //options: 
  //-0 was up AND is still up: nothing happened
  //-1 was up AND it now down: just clicked
  //-2 was down AND is still down: increase pressed time
  //-3 was down AND now is UP: just released
  
  int rEv;
  boolean bDown = isButtonDown();
  
  if(!oldBut){
    if(!bDown){
      rEv = 0;
    }else{
      rEv = 1;
      lastClickTime = millis();
      lastHoldTime = 0;
    }
  }else{
    if(bDown){
      rEv = 2;
      lastHoldTime = millis()-lastClickTime;
    }else{
      rEv = 3;
    }
  }
  
  oldBut = bDown;
  return rEv;
}
