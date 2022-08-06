#include "memory.h"
#include "menu.h"
#include "keypadW.h"

//----Address EEPROM----
#define HIGH_TEMP_ADDRESS 0
#define LOW_TEMP_ADDRESS 3
#define ALARM_TEMP_ADDRESS 6
#define LIGHT_ADDRESS 9
#define MICRO_ADDRESS 12

//----Variables----
//System setting variables
int highTemp=0, lowTemp=0, alarmTemp=0, light=0, micro=0;

//----load----
void loadSystemValues(){
  getEeprom(HIGH_TEMP_ADDRESS,highTemp);
  getEeprom(LOW_TEMP_ADDRESS,lowTemp);
  getEeprom(ALARM_TEMP_ADDRESS,alarmTemp);
  getEeprom(LIGHT_ADDRESS,light);
  getEeprom(MICRO_ADDRESS,micro);
}

//----setup----
void setupSetting(){
  loadSystemValues();
}

//----Getters----
int getHighTemp(){
  return highTemp;
}
int getLowTemp(){
  return lowTemp;
}
int getAlarmTemp(){
  return alarmTemp;
}
int getLight(){
  return light;
}
int getMicro(){
  return micro;
}

//----Setters----
void set(int &value, int address, int minValue, int maxValue){
  int auxValue=-2;
  readIn(auxValue);
  if(minValue<auxValue && auxValue<maxValue){
    putEeprom(address,auxValue);
    value=auxValue;
    successfulMessage();
  }
  else wrongMessage();
}
//Option 0.0: setHighTemp
void setHighTemp(){
  set(highTemp,HIGH_TEMP_ADDRESS,lowTemp,110);
}
//Option 0.1: setLowTemp
void setLowTemp(){
  set(lowTemp,LOW_TEMP_ADDRESS,-1,highTemp);
}
//Option 0.2: setAlarmTemp
void setAlarmTemp(){
  set(alarmTemp,ALARM_TEMP_ADDRESS,highTemp,110);
}
//Option 1.0: setLight
void setLight(){
  set(light,LIGHT_ADDRESS,0,1000);
}
//Option 2.0: setMicro
void setMicro(){
  set(micro,MICRO_ADDRESS,0,100);
}
//Option 3.0: resetVaalues
void resetValues(){
  highTemp=25;
  putEeprom(HIGH_TEMP_ADDRESS,highTemp);
  lowTemp=15;
  putEeprom(LOW_TEMP_ADDRESS,lowTemp);
  alarmTemp=40;
  putEeprom(ALARM_TEMP_ADDRESS,alarmTemp);
  light=850;
  putEeprom(LIGHT_ADDRESS,light);
  micro=30;
  putEeprom(MICRO_ADDRESS,micro);
  successfulMessage();
}

//----options settingMenu----
//--Option 0: setTempMenu
void showSetTempMenu(int pos){
  if(pos<2) showOptions("HighTemp ",highTemp,"LowTemp",lowTemp);
  else showOptions("AlarmTemp",alarmTemp,"Back        ");
}
bool processSetTempMenu(int pos){
  if(pos==0) setHighTemp();
  else if(pos==1) setLowTemp();
  else if(pos==2) setAlarmTemp();
  else if(pos==3) return true;
  return false;
}
void setTempMenu(){
  funcMenu(showSetTempMenu,processSetTempMenu,3);
}
//--Option 1: setLightMenu
void showSetLightMenu(int pos){
  showOptions("SetLight",light,"Back");
}
bool processSetLightMenu(int pos){
  if(pos==0) setLight();
  else if(pos==1) return true;
  return false;
}
void setLightMenu(){
  funcMenu(showSetLightMenu,processSetLightMenu,1);
}
//--Option 2: setMicroMenu
void showSetMicroMenu(int pos){
  showOptions("SetMicro",micro,"Back");
}
bool processSetMicroMenu(int pos){
  if(pos==0) setMicro();
  else if(pos==1) return true;
  return false;
}
void setMicroMenu(){
  funcMenu(showSetMicroMenu,processSetMicroMenu,1);
}
//--Option 3: resetValuesMenu
void showResetValuesMenu(int pos){
  showOptions("Ok","Back");
}
bool processResetValuesMenu(int pos){
  if(pos==0) resetValues();
  else if(pos==1) return true;
  return false;
}
void resetValuesMenu(){
  funcMenu(showResetValuesMenu,processResetValuesMenu,1);
}
//Setting - menu
void showSettingMenu(int pos){
  if(pos<2) return showOptions("UTemp ","ULight");
  if(pos<4) showOptions("UMicro","Reset ");
  else showOptions("Back  ","      ");
}
bool processSettingMenu(int pos){
  switch(pos){
    case 0:
      setTempMenu(); break;
    case 1:
      setLightMenu(); break;
    case 2:
      setMicroMenu(); break;
    case 3: 
      resetValuesMenu(); break;
    case 4:
      return true; //Back
  }
  return false;
}
void settingMenu(){
  funcMenu(showSettingMenu,processSettingMenu,4);
}
