#include <arduino.h>
#include <LiquidCrystal.h>
//----Initialize LiquidCrystal----
LiquidCrystal lcd {12,11,5,4,3,2};//Pinouts: RS, En, D4, D5, D6, D7
//----Setup----
void setupLcd(){
  lcd.begin(16, 2);
}
//----lcd functions----
void lcdSetPrint(int c, int f, char message[]){
  lcd.setCursor(c, f);
  lcd.print(message);
}
void lcdSetPrint(int c, int f, int value){
  lcd.setCursor(c, f);
  lcd.print(value);
}
void lcdSetPrint(int c, int f, float value){
  lcd.setCursor(c, f);
  lcd.print(value);
}
void lcdSetPrint(int c, int f, char value){
  lcd.setCursor(c, f);
  lcd.print(value);
}
void clearScreen(){
  lcd.clear();
}
//----message in lcd----
void message(char value[]){
  clearScreen();
  lcdSetPrint(2,0,value);
  delay(2000);
  clearScreen();
}
void successfulMessage(){
  message("Successful!");
}
void wrongMessage(){
  message("Wrong!");
}
