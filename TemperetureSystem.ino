#include <LiquidCrystal.h>

//Initialize LiquidCrystal
LiquidCrystal lcd {12,11,5,4,3,2};//Pinouts: RS, En, D4, D5, D6, D7.

//Pin connection for RGB LED (Always in the PWM field)
#define REDPIN 8
#define GREENPIN 9
#define BLUEPIN 10

//Pin connection for Temperature Sensor
#define TEMPSENSOR A0
#define LIGHTSENSOR A1
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistorvoid setup()
//Initialize SYSTEM TEMPERATURE variables
int pos=0;
int tempValue=0;
int lightValue=0;

void setup() {
  
  
  //Initialize RGB LED
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  lcd.begin(16, 2); 
}

void loop() {
  lightSystem2();
}
void tempSystem2(){
  //read thermistor value
  long a =1023 - analogRead(TEMPSENSOR);
  //the calculating formula of temperature
  float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  float tempF = tempC + 273.15;
  // Print a message of “Temp: “to the LCD.
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  // Print a centigrade temperature to the LCD.
  lcd.print(tempC);
  // Print the unit of the centigrade temperature to the LCD.
  lcd.print(" C");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("Fahr: ");
  // Print a Fahrenheit temperature to the LCD.
  lcd.print(tempF);
  // Print the unit of the Fahrenheit temperature to the LCD.
  lcd.print(" F");
  delay(200); //wait for 100 milliseconds
}
void lightSystem2(){
  lightValue = analogRead(LIGHTSENSOR);
  lcd.setCursor(0, 0);
  lcd.print("Photocell:");
  lcd.setCursor(11, 0);
  lcd.print(lightValue);//print the temperature on lcd1602
  //Serial.println(lightValue);
  delay(1000);
  lcd.clear();
  lcd.setCursor(11, 0);
  lcd.print(" ");
}
void tempSystem(){
  tempValue=analogRead(TEMPSENSOR);
  lcdSetPrint(0,0,"TEMPERATURE");
  lcdSetPrint(0,1,tempValue);
  if(tempValue>25){
    setColor(255,0,0);  //RGB turn-on red
  }else{
    if(tempValue<18){
      setColor(0,0,255);//RGB turn-on blue
    }
    else
      setColor(0,255,0);//RGB turn-on green
  }
    delay(1000);
}
void lightSystem(){
  lightValue=analogRead(LIGHTSENSOR);
  lcdSetPrint(0,0,"LIGHT");
  lcdSetPrint(0,1,lightValue);
  if(lightValue>200){
    setColor(128,0,128); //RGB turn-on purple
  }else{
      setColor(255,233,0); //RGB turn-on yellow
  }
    delay(500);
}
void setColor(int red, int green, int blue){
  analogWrite(REDPIN,red);
  analogWrite(GREENPIN,green);
  analogWrite(BLUEPIN,blue);
}
void ledWith(int r, int g, int b, int time_ms){
  setColor(r,g,b);
  delay(time_ms);
}
void lcdSetPrint(int c, int f, char message[]){
  lcd.setCursor(c, f);
  lcd.print(message);
}
void lcdSetPrint(int c, int f, int value){
  lcd.setCursor(c, f);
  lcd.print(value);
}
void lcdSetPrint(int c, int f, char value){
  lcd.setCursor(c, f);
  lcd.print(value);
}
