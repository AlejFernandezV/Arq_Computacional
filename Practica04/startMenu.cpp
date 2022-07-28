#include "menu.h"
#include "setting.h"
#include "stateMachine.h"

//----Setup----
void setupStartMenu(){
  setupSetting();
}

//----Start-menu----
void showStartMenu(int pos){
  if(pos<2) showOptions("Setting","Run");
  else showOptions("Back   ","   ");
}
bool processStartMenu(int pos){
  if(pos==0) { settingMenu(); return false; }
  if(pos==1) setInput(1);//To run
  if(pos==2) setInput(2);//Back to security
  return true;
}
void startMenuState(){
  funcMenu(showStartMenu,processStartMenu,2);
}
