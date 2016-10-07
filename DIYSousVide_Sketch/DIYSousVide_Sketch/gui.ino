#include <Arduino.h>


void initLCD() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("INIT SCREEN");
}

void showTemp(int t) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatur: ");
  lcd.print(t);
  lcd.print(" °C");
}

void showTime(int tM, int tH){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zeit: ");
  lcd.print(tH);
  lcd.print(" Hours ");
  lcd.print(tM);
  lcd.print(" Minutes");
}
void showCurrentTime(){

  long cT = startTime-millis();

  int tH = (int)(((cT/1000)/60)/60);
  int tM = (int)(((cT/1000)/60)%60);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Zeit: ");
  lcd.print(tH);
  lcd.print(" Hours ");
  lcd.print(tM);
  lcd.print(" Minutes");
  
  }
