#include <Keypad.h>
#include "lcd.h"
#include "rotaryEncoder.h"
#include <stdlib.h>

//----Initialize Keypad----
#define ROWS 4 //four rows
#define COLS 3 //three columns
char keys[ROWS][COLS] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 24, 26}; //connect to the column pinouts of the keypad

//----Variables----
Keypad keypad=Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//----getters----
char getKeyAux(){
  return keypad.getKey();
}

//----Read value from keypad- functions
void clear(char value[]){
  value[0]='*';
  value[1]='*';
  value[2]='*';
}
void add(char key,int &pos, char value[]){
  lcdSetPrint(pos,1,key);
  value[pos]=key;
  pos++;
}
void removeIn(int &pos, char value[]){
  if(pos>0){
    pos--; 
    lcdSetPrint(pos,1,' ');
    value[pos]='*';
  }
}
void readIn(int &value){
  clearScreen();
  int auxPos=0;
  char auxValue[3]={'*','*','*'};
  bool auxBack=false;
  lcdSetPrint(0,0,"Reading:");
  while(!auxBack){
    char key = getKeyAux();
    if(isPressedRotary()) {
      if(auxValue[0]!='*'){
        value=atoi(auxValue);
        clear(auxValue);
      }
      return clearScreen();
    }
    if(key){
      if(key=='*') removeIn(auxPos,auxValue);
      else if(auxPos<3) add(key,auxPos,auxValue);
    }
  }
}
