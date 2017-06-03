void heaterOn(){
  digitalWrite(heaterPin,HIGH);
  lcd.setCursor(15,1);
  lcd.print("H");
  }
void heaterOff(){
  digitalWrite(heaterPin,LOW);

  lcd.setCursor(15,0);
  lcd.print(" ");
  }

boolean noTimeLeft(){
  
  return false;
  }
