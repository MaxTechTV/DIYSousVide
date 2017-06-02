void heaterOn(){
  digitalWrite(heaterPin,LOW);
  lcd.setCursor(15,0);
  lcd.print("H");
  }
void heaterOff(){
  digitalWrite(heaterPin,HIGH);

  lcd.setCursor(15,0);
  lcd.print(" ");
  }
