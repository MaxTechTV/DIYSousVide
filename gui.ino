
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



