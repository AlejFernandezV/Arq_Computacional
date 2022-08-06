#include <arduino.h>
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
//----getters----
float getTempValue(){
  long a=1023-analogRead(TEMP);   //read thermistor value
  float tempC=BETA/(log((1025.0*10/a-10)/10)+BETA/298.0)-273.0;  //the calculating formula of temperature
  return tempC;
}
int getMicroValue(){
  analogRead(MICRO);
}
int getLightValue(){
  analogRead(LIGHT);
}
