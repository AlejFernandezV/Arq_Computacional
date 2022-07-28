#include "AsyncTaskLib.h"
#include "rotaryEncoder.h"
#include "sensorController.h"
#include "stateMachine.h"
//----Initialize AsynkTask----
AsyncTask asyncTaskTemp(2000,true, tempSystem);
AsyncTask asyncTaskLight(1000,true, lightSystem);
AsyncTask asyncTaskMicro(1000, true, microSystem);

void setupTaskManager(){
  setupSensorController();
  asyncTaskTemp.Start();
  asyncTaskLight.Start();
  setupRotaryEncoder();
  Serial.println("Tasks started");
  setInput(3);
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
