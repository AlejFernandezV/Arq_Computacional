#include <arduino.h>
//----Pin connections----
//RGB LED (Always in the PWM field)
#define REDPIN 8
#define GREENPIN 9
#define BLUEPIN 10
//----Setup----
void setupRgb(){
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);  
}
//----led RGB - functions----
void setColor(int red, int green, int blue){
  analogWrite(REDPIN,red);
  analogWrite(GREENPIN,green);
  analogWrite(BLUEPIN,blue);
}
void ledWith(int r, int g, int b, int time_ms){
  setColor(r,g,b);
  delay(time_ms);
}
