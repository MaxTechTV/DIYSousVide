void initLCD() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DIYSousVide v1.1");
  lcd.setCursor(0,1);
  lcd.print("by MaxTechTV");
 
  delay(1000);
}

void showTemp(int t) {
  lcd.setCursor(0, 0);
  lcd.print("Temp:      ");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.print(" C");
}

void showTime(int tH,int tM){
  lcd.setCursor(0, 0);
  lcd.print("Zeit:          ");
  lcd.setCursor(6, 0);
  lcd.print(tH);
  lcd.print(" h ");
  lcd.print(tM);
  lcd.print(" min");
}
void showCurrentTime(){

  long cT = millis()-startTime;

  int tH = (int)(((cT/1000)/60)/60);
  int tM = (int)(((cT/1000)/60)%60);
  lcd.setCursor(0, 1);
  lcd.print("Zeit:          ");
  lcd.setCursor(6, 1);
  lcd.print(targetHours-tH);
  lcd.print("h ");
  lcd.print(targetMinutes-tM);
  lcd.print("min");

  }
