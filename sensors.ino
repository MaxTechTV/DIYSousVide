void initSensors(){
lcd.begin();
sensors.begin();
}


boolean checkEnc() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    return true;
  }
    else {
      return false;
    }
  }

