#include <arduino.h>

//----Pin connections----
#define CLKPIN 32
#define DTPIN 34
#define SWPIN 36

//----Variables----
bool clkState  = LOW;
bool clkLast  = HIGH;
bool swState  = HIGH;
bool swLast  = HIGH;

//Timer
unsigned long initTime=0,finalTime=0;

//----Setup----
void setupRotaryEncoder(){
  pinMode(CLKPIN,INPUT);
  pinMode(DTPIN,INPUT);
  pinMode(SWPIN,INPUT_PULLUP);
}

//----rotary encoder functions----
void readRotary(int &rotVal, int maxOption) {
  clkState = digitalRead(CLKPIN);
  if ((clkLast == LOW) && (clkState == HIGH)) {//rotary moving
    Serial.print("Rotary position ");
    if (digitalRead(DTPIN) == HIGH) {
      rotVal--;
      if ( rotVal < 0 ) rotVal = 0;
    }
    else {
      rotVal++;
      if ( rotVal > maxOption ) rotVal = maxOption;
    }
    Serial.println(rotVal);
  }
  clkLast = clkState;
}
bool isPressedRotary(){
  swState = digitalRead(SWPIN);
  if (swState == LOW && swLast == HIGH) {
    Serial.println("Rotary pressed");
    delay(500);//debounce
    swLast = swState;
    return true;
  }
  swLast = swState;
  return false;
}
bool isDownRotary(){
  swState = digitalRead(SWPIN);
  if (swState == LOW && swLast == HIGH) initTime=millis();
  swLast = swState;
  if(swState == LOW && swLast == LOW) finalTime=millis();
  if(finalTime>initTime+3000) return true;
  return false;
}
