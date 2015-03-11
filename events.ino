void onClick(){

}

void onHold(){
  if(mode!=MODE_DAZ){
    if(lastHoldTime>500){
      startDazzle();
    }
  }else{
    updateDazzle();
  }
}

void onReleased(){
  if(mode==MODE_OFF){
    if(lastHoldTime>50){
      turnOn();
    }
  }else if(mode==MODE_ON){
    if(lastHoldTime>50){
      turnOff();
    }
  }else if(mode==MODE_DAZ){
    if(dd.lastMode==MODE_ON){
      turnOn();
    }else if(dd.lastMode==MODE_OFF){
      turnOff();
    }
  }
}
