/*
---------------------------------------------------------
DIYSousVide Version 1.1
Author: Max, Host of MaxTechTV
Date: 11.10.16
First partly Working Release with basic Functionality 

- 16x2 Display shows Information
- Rotary Encoder enables Input of Temperature & Time
- Relay triggers Heater 
- Time counts backwards
- Basic Temp Management implemented (no PID support yet)

License: released under CC-BY-NC-4 (https://creativecommons.org/licenses/by-nc/4.0/)
---------------------------------------------------------
*/


// LIBRARIES

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h> //https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <Encoder.h> //https://github.com/PaulStoffregen/Encoder


// CONFIG I/O
int encPin1 = 2;
int encPin2 = 3;
int encPinClick = 7;
int tempSensorPin = 8;
int heaterPin = 4;

#define ONE_WIRE_BUS tempSensorPin

Encoder myEnc(encPin1, encPin2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// CONFIG VARIABLES
int mode = 1;

long oldPosition  = 0;

int upperTempLimit = 100;
int lowerTempLimit = 0;

int targetTemp = 30;
int currentTemp = 0;
int deltaHys = 50;

int targetMinutes = 0;
int targetHours = 0;
int time_cache= 0;

int currentMinutes = 0;
int currentHours = 0;

long startTime = 0;


// SETUP
void setup()
{
  initLCD();
  initSensors();
  pinMode(encPinClick,INPUT_PULLUP);
  pinMode(heaterPin,OUTPUT);
  digitalWrite(heaterPin, HIGH);
  showTemp(targetTemp);
  //Serial.begin(9600);

}

void loop()
{

  // MODE 0 - Choose Preset 

  // to be implemented... 
  
  // MODE 1 - Set Temperature
  
  while (mode == 1) {

  if (!digitalRead(encPinClick)) {

      mode = 2;
      targetTemp=targetTemp*10;
      while(!digitalRead(encPinClick));
      delay(100);
      lcd.clear();
      showTime(targetHours, targetMinutes);
      break;
    }
      int targetTemp_old = targetTemp;
      targetTemp = targetTemp+checkEnc();

      if ((targetTemp_old-targetTemp != 0)){
      if (targetTemp >= upperTempLimit) {
        targetTemp = upperTempLimit;
      }
      else if (targetTemp <= lowerTempLimit) {
        targetTemp = lowerTempLimit;
        
      }
      showTemp(targetTemp);
    }
  }

  // MODE 2 - Set time 

  while (mode == 2) {
    if (!digitalRead(encPinClick)) {
      mode = 3;
      while(!digitalRead(encPinClick));
      delay(100);
      startTime = millis();
      lcd.clear();
      showTemp(0);
      showCurrentTime();
      break;
    }

      int time_cache_old = time_cache;
      time_cache =time_cache+checkEnc();
      if ((time_cache_old - time_cache)!=0){
      
      targetHours = time_cache / 60;
      targetMinutes = time_cache % 60;
    
     showTime(targetHours, targetMinutes);
      }

  }

  // MODE 3 - Start Cooking 
  
   while (mode == 3) {
    if (!digitalRead(encPinClick)) {
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
    currentTemp=measureTemp(3);
    showTemp(currentTemp/10);
    showCurrentTime();

  }
}
