void setLight(int bgt, byte drvMode){
  pinMode(DPIN_PWR, OUTPUT);
  digitalWrite(DPIN_PWR, HIGH);
  digitalWrite(DPIN_DRV_MODE, drvMode);
  analogWrite(DPIN_DRV_EN, bgt);
}

void turnOff(){
  mode = MODE_OFF;
  setLight(0,LOW);
  oldBut = false;
  lastHoldTime = 0;
}

void turnOn(){
  mode = MODE_ON;
  setLight(200,HIGH);
}

void startDazzle(){
  dd.lastMode = mode;
  refreshDazzleData();
  setLight(dd.bgt, HIGH);
  
  mode = MODE_DAZ;
}

void refreshDazzleData(){
  dd.lastTime = millis();
  dd.bgt = dd.bgt>0?0:random(100,255);
  //15hz - 55hz
  dd.interval = 1000.0/random(15,55);
}

void updateDazzle(){
  if(millis()>(dd.lastTime+dd.interval)){
    refreshDazzleData();
    setLight(dd.bgt, HIGH);
  }
}
