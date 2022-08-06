/**
 * @file
 * This is the file that contains what is necessary for the alarm state.
 */
#include "buzzer.h"
#include "stateMachine.h"

/**
 * Alarm state.
 * In the alarm state, a song plays and then changes to startMenuState().
 */
void alarmState(){
  song();
  setInput(1); //To setting
}
