#include <arduino.h>
#include "lcd.h"
#include "stateMachine.h"
#include "rgb.h"
#include "keypadW.h"
#include "security.h"

#define WAIT_KEY 6000

//----Variables----
char enterCode[6]={'0','0','0','0','0','0'};
int pos=0, attempt=0; 
unsigned long initTimeKey=0,finalTimeKey=0;

//----Setup----
void setupSecurity(){
  setupLcd();
  setupRgb();
//  setupKeypad();
}

//----security system----
void wrongPassword(){
  lcdSetPrint(0,1," WRONG!");
  setColor(255,128,0); //Orange and wait 2 seconds.
  delay(2000);
  if(attempt<2){
    lcdSetPrint(0,1,"TRY AGAIN!");
    setColor(0,0,0); //Led turn off...
    delay(2000);
    }
  attempt++;
  pos=0;
  clearScreen();
}
void correctPassword(){
  lcdSetPrint(0,1,"CORRECT");
  delay(1500);
  clearScreen();
  lcdSetPrint(0,0,"WELCOME");
  setColor(0,255,0);  //Green
  delay(2000);
  setColor(0,0,0);
  pos=attempt=0; 
  clearScreen();
  setInput(1); //To setMenu
}
void unlockSystem(){
  finalTimeKey=millis();
  if(finalTimeKey>initTimeKey+WAIT_KEY && initTimeKey!=0){
    initTimeKey=0;
    for(int i =0;i<6;i++){
      enterCode[i]='*';
    }
    wrongPassword();
    clearScreen();
    pos=0;
  }
  lcdSetPrint(0,0,"PASSWORD:");
  char key = getKeyAux();
  
  if(key=='#'||pos==6) {//check
    char secretCode[6] = {'8','7','6','1','8','9'};//System password
    for(pos=0;pos<6;pos++){
      if(enterCode[pos]!=secretCode[pos]) return wrongPassword();
    }
    correctPassword();
  }
  if(key) {//add
    initTimeKey=millis();
    lcdSetPrint(pos,1,"*");
    enterCode[pos]=key;
    pos++;
  }
}
void lockSystem(){
  lcdSetPrint(0,0,"SYSTEM LOCKED");
  setColor(255,0,0);  //Led RGB Turn-On Red
  delay(5000);
  setColor(0,0,0);    //Turn-off RGB
  delay(2000);
  pos=attempt=0;
  clearScreen();
}
void securityState(){
  if(attempt < 3) unlockSystem();
  else lockSystem();
}
