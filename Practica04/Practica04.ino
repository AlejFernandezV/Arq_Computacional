/**
 * @file
 * This is the main file of the project, it calls the setup() 
 * and loop() functions of the Arduino systems.
 */

#include <LiquidCrystal.h>
#include "stateMachine.h"

void setup(){
  setupStateMachine();  
}
void loop(){
  runStateMachine();
}
