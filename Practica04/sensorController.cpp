#include <arduino.h>
#include "lcd.h"
#include "rgb.h"
#include "setting.h"
#include "stateMachine.h"

//----Pin connections----
#define TEMP A0
#define LIGHT A1
#define MICRO A2
#define DO_MICRO 26
#define LED_MICRO 13

//----Maths----
#define BETA 4090

//----Setup----
void setupSensorController(){
  pinMode(LED_MICRO,OUTPUT);
}

//----temp functions----
float getTempValue(){
  long a=1023-analogRead(TEMP);   //read thermistor value
  float tempC=BETA/(log((1025.0*10/a-10)/10)+BETA/298.0)-273.0;  //the calculating formula of temperature
  return tempC;
}

//----system functions----
void microSystem(){
  int soundValue = analogRead(MICRO);
  lcdSetPrint(6,0,"     ");  
  lcdSetPrint(6,0,soundValue);
  Serial.print(millis()/1000);
  Serial.print(", read micro: ");
  Serial.println(soundValue);
  if(soundValue >getMicro()){
    digitalWrite(LED_MICRO,HIGH);
    delay(2000);
  }
  else digitalWrite(LED_MICRO,LOW);
}
void tempSystem(){
  float tempValue=getTempValue();
  lcdSetPrint(0,0,"Temp:"); 
  lcdSetPrint(7,0,"        ");  
  lcdSetPrint(7,0,tempValue);
  Serial.print(millis()/1000);
  Serial.print(", read temp: "); //1,read temp 24 C
  Serial.println(tempValue);
  if(tempValue>getAlarmTemp()) setInput(1); //To alarm
  else if(tempValue>getHighTemp()) {
    setColor(255,0,0);  //RGB turn-on red
  }
  else if(tempValue<getLowTemp()) setColor(0,0,255);//RGB turn-on blue
  else setColor(0,255,0);//RGB turn-on green
}
void lightSystem(){
  int lightValue=analogRead(LIGHT);
  lcdSetPrint(0,1,"Light:");
  lcdSetPrint(7,1,"       ");
  lcdSetPrint(7,1,lightValue);
  Serial.print(millis()/1000);
  Serial.print(", read light: ");
  Serial.println(lightValue);
  if(lightValue>getLight()) setColor(128,0,128); //RGB turn-on purple
  else setColor(255,233,0); //RGB turn-on yellow
}
