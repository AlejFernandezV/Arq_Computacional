#include <arduino.h>
#include "AsyncTaskLib.h"
#include "rgb.h"
#include "setting.h"
#include "lcd.h"
#include "rotaryEncoder.h"
#include "sensorController.h"
#include "stateMachine.h"
//----System functions signature----
void tempSystem();
void lightSystem();
void microSystem();

//----Initialize AsynkTask----
AsyncTask asyncTaskTemp(2000,true, tempSystem);
AsyncTask asyncTaskLight(1000,true, lightSystem);
//AsyncTask asyncTaskMicro(1000, true, microSystem);

void setupTaskManager(){
  setupSensorController();
  asyncTaskTemp.Start();
  asyncTaskLight.Start();
  setupRotaryEncoder();
  Serial.println("Tasks started");
  //setInput(3);
}

//----taskManager----
void taskManagerState(){
  asyncTaskTemp.Update();
  asyncTaskLight.Update();
  if(isDownRotary()){
    setInput(2); //back to settingMenu
  }
  if(getInput()!=3){//When the state changes, the tasks finish.
    asyncTaskTemp.Stop();
    asyncTaskLight.Stop();
    Serial.println("Tasks finished");
  }
}
//----system functions----
void microSystem(){
  int soundValue = getMicroValue();
  lcdSetPrint(6,0,"     ");  
  lcdSetPrint(6,0,soundValue);
  Serial.print(millis()/1000);
  Serial.print(", read micro: ");
  Serial.println(soundValue);
  /*if(soundValue >getMicro()){
    digitalWrite(LED_MICRO,HIGH);
    delay(2000);
  }
  else digitalWrite(LED_MICRO,LOW);*/
}
void tempSystem(){
  float tempValue=getTempValue();
  lcdSetPrint(0,0,"Temp:"); 
  lcdSetPrint(7,0,"        ");  
  lcdSetPrint(7,0,tempValue);
  Serial.print(millis()/1000);
  Serial.print(", read temp: "); //1,read temp 24 C
  Serial.println(tempValue);
  if(tempValue>getAlarmTemp()) setInput(1); //To alarm
  else if(tempValue>getHighTemp()) {
    setColor(255,0,0);  //RGB turn-on red
  }
  else if(tempValue<getLowTemp()) setColor(0,0,255);//RGB turn-on blue
  else setColor(0,255,0);//RGB turn-on green
}
void lightSystem(){
  int lightValue=getLightValue();
  lcdSetPrint(0,1,"Light:");
  lcdSetPrint(7,1,"       ");
  lcdSetPrint(7,1,lightValue);
  Serial.print(millis()/1000);
  Serial.print(", read light: ");
  Serial.println(lightValue);
  if(lightValue>getLight()) setColor(128,0,128); //RGB turn-on purple
  else setColor(255,233,0); //RGB turn-on yellow
}
