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

int measureTemp(int d){

   if (d==0){
    sensors.requestTemperatures();
    int temp = (int)(sensors.getTempCByIndex(0)*10);
    return temp;
   }
   else{
    int temp = 0;
    for (int i = 0; i<d;i++){
      sensors.requestTemperatures();
      temp =+ (int)(sensors.getTempCByIndex(0)*10);
      delay(100);
    }
    temp = temp/d;
    return temp;
    }
}
