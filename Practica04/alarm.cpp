#include "buzzer.h"
#include "stateMachine.h"

void alarmState(){
  song();
  setInput(1); //To setting
}
