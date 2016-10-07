#include <Arduino.h>

// The used Libraries

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h> //https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Encoder.h> //https://github.com/PaulStoffregen/Encoder



int encPin1 = 5;
int encPin2 = 6;
int encPinClick = 7;
int tempSensorPin = 8;

#define ONE_WIRE_BUS tempSensorPin

Encoder myEnc(encPin1, encPin2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int mode = 0;

long oldPosition  = 0;

int upperTempLimit = 95;
int lowerTempLimit = 30;

int targetTemp = 0;
int deltaHys = 50;

int targetMinutes = 0;
int targetHours = 0;

int currentMinutes = 0;
int currentHours = 0;

long startTime = 0;

void setup()
{
  initLCD();
  initSensors();
}

void loop()
{
  while (mode == 1) {
    if (digitalRead(!encPinClick)) {
      oldPosition = 0;
      mode = 2;
      targetTemp=targetTemp*10;
      break;
    }
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

  while (mode == 2) {
    if (digitalRead(!encPinClick)) {
      mode = 3;
      startTime = millis();
      break;
    }
    if (checkEnc()) {
      int newTime = oldPosition;
      int targetHours = newTime / 60;
      int targetMinutes = newTime % 60;
    }
    showTime(targetHours, targetMinutes);
  }

   while (mode == 3) {
    if (digitalRead(!encPinClick)) {
      mode = 4;
      break;
    }
    int currentTemp = measureTemp(3);
    if (currentTemp<(targetTemp-deltaHys)){
      heaterOn();
      }
    if (currentTemp>(targetTemp+deltaHys)){
      heaterOff();
    }

    showTemp(currentTemp/10);
    showCurrentTime();
    
  }
}

