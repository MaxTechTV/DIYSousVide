void initSensors(){
lcd.begin();
sensors.begin();
}


int checkEnc() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    int delta = oldPosition-newPosition;
    oldPosition = newPosition;

    if(delta>0) return 1;
    else if (delta<0) return-1;
    return delta;
  }
    else {
      return 0;
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
      temp =temp+ (int)(sensors.getTempCByIndex(0)*10);
      delay(10);
    }
    temp = temp/d;
    return temp;
    }
}
