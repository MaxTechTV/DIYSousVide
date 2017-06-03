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


float measureTemp(int d){

   if (d==0){
    sensors.requestTemperatures();
    float temp = (int)(sensors.getTempCByIndex(0));
    return temp;
   }
   else{
    float temp = 0;
    for (int i = 0; i<d;i++){
      sensors.requestTemperatures();
      temp =temp+ (sensors.getTempCByIndex(0));
      
      delay(10);
    }
    temp = temp/d;
    return temp;   
    }
}


void safetyNet(){
  if (currentTemp<0 || currentTemp > 1000) {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ERROR");

    digitalWrite(heaterPin,LOW);
    }

   for (int i = 0; i<1000;i++){
    }
   while(true);
}

