// The used Libraries

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h> //https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Encoder.h> //https://github.com/PaulStoffregen/Encoder

#define ONE_WIRE_BUS 8

Encoder myEnc(5, 6);
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int mode = 0;

long oldPosition  = 0;

int upperTempLimit;
int lowerTempLimit;

int targetTemp = 0;

void setup()
{
  initLCD();
  initSensors();
}

void loop()
{
  while (mode == 1) {

    if (checkEnc()) {

      int newTemp = oldPosition;
      if (newTemp >= upperTempLimit) {
        newTemp = upperTempLimit;
        oldPosition = upperTempLimit;
      }
      else if (newTemp <= lowerTempLimit) {
        newTemp = lowerTempLimit;
        oldPosition = lowerTempLimit;
      }
      else {
        targetTemp = newTemp;
      }
      showTemp(targetTemp);
    }
  }
sensors.requestTemperatures();
lcd.print(sensors.getTempCByIndex(0));
}



