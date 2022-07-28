#include "lcd.h"
#include "rotaryEncoder.h"
//----Show options on lcd for menu- functions----
void showOptions(char upOption[], char downOption[]){
  lcdSetPrint(1,0,upOption);
  lcdSetPrint(1,1,downOption);
}
void showOptions(char upOption[],int upValue, char downOption[]){
  lcdSetPrint(1,0,upOption);
  lcdSetPrint(10,0,upValue);
  lcdSetPrint(1,1,downOption);
}
void showOptions(char upOption[],int upValue, char downOption[],int downValue){
  lcdSetPrint(1,0,upOption);
  lcdSetPrint(10,0,upValue);
  lcdSetPrint(1,1,downOption);
  lcdSetPrint(10,1,downValue);
}
void showSelected(int pos, char flag){
  char aux=' ';
  if(pos%2==0){//up
    lcdSetPrint(0,0,flag);
    lcdSetPrint(0,1,aux);
  }
  else{//down
    lcdSetPrint(0,0,aux);
    lcdSetPrint(0,1,flag);
  }
}
//----Iterate menu with show and process functions----
void funcMenu(void (* fShow)(int pos), bool (*fProcess )(int pos),int nOpt) {  // funcion aceptando un puntero-a-función
  clearScreen();
  int posMenu=0;
  bool back=false;
  setupRotaryEncoder();
  do{
    readRotary(posMenu,nOpt);
    fShow(posMenu);
    showSelected(posMenu,'-');
    if(isPressedRotary()) back=fProcess(posMenu);
  }while(back==false);
  clearScreen();
}
