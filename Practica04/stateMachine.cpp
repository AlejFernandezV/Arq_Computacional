#include "StateMachineLib.h"
#include "security.h"
#include "startMenu.h"
#include "taskManager.h"
#include "alarm.h"

//----Initialize StateMachine----
// Alias
enum State {
  PosicionA = 0,
  PosicionB = 1,
  PosicionC = 2,
  PosicionD = 3
};
enum Input {  
  Reset=0,
  Forward=1,
  Backward=2,
  Unknown=3,
  };
// Stores last user input
Input input;
//----Create new StateMachine----
StateMachine stateMachine(4, 9);

//----setters-----
void setInput(int value){
  input = static_cast<Input>(value);
}
//----setters-----
int getInput(){
  return static_cast<int>(input);
}
//----Auxiliar output functions that show the state debug----
void outputA(){//security
  Serial.println("A   B   C   D");
  Serial.println("X            ");
  Serial.println();
  input=Input::Unknown;
  Serial.println(input);
  setupSecurity();
}
void outputB(){//startMenu
  Serial.println("A   B   C   D");
  Serial.println("    X        ");
  Serial.println();
  input=Input::Unknown;
  Serial.println(input);
  setupStartMenu();
}
void outputC(){//taskManager
  Serial.println("A   B   C   D");
  Serial.println("        X    ");
  Serial.println();
  input=Input::Unknown;
  Serial.println(input);
  setupTaskManager();
}
void outputD(){//alarm
  Serial.println("A   B   C   D");
  Serial.println("            X");
  Serial.println();
  input=Input::Unknown;
  Serial.println(input);
}

//----Setup----
void setupStateMachine(){
  Serial.begin(9600);
  // Add transitions
  stateMachine.AddTransition(PosicionA, PosicionB, []() { return input == Forward; });
  stateMachine.AddTransition(PosicionB, PosicionA, []() { return input == Backward; });
  stateMachine.AddTransition(PosicionB, PosicionC, []() { return input == Forward; });
  stateMachine.AddTransition(PosicionC, PosicionB, []() { return input == Backward; });
  stateMachine.AddTransition(PosicionC, PosicionD, []() { return input == Forward; });
  stateMachine.AddTransition(PosicionD, PosicionB, []() { return input == Forward; });
  // Add actions
  stateMachine.SetOnEntering(PosicionA, outputA);
  stateMachine.SetOnEntering(PosicionB, outputB);
  stateMachine.SetOnEntering(PosicionC, outputC);
  stateMachine.SetOnEntering(PosicionD, outputD);
  stateMachine.SetOnLeaving(PosicionA, []() {Serial.println("Leaving A"); });
  stateMachine.SetOnLeaving(PosicionB, []() {Serial.println("Leaving B"); });
  stateMachine.SetOnLeaving(PosicionC, []() {Serial.println("Leaving C"); });
  stateMachine.SetOnLeaving(PosicionD, []() {Serial.println("Leaving D"); });
  // Initial state
  stateMachine.SetState(PosicionA, false, true);
}

//----Auxiliar function that reads the user input----
int readInput(){
  Input currentInput = Input::Unknown;
  if (Serial.available())
  {
    char incomingChar = Serial.read();
    switch (incomingChar)
    {
      case 'R': currentInput = Input::Reset;  break;
      case 'A': currentInput = Input::Backward; break;
      case 'D': currentInput = Input::Forward; break;
      default: break;
    }
  }
  return currentInput;
}

//----run----
void runStateMachine(){
  // Update State Machine
  int currentState = stateMachine.GetState();
  switch (currentState)
  {
    case PosicionA: securityState();
                    break;
    case PosicionB: startMenuState(); 
                    break;
    case PosicionC: taskManagerState(); 
                    break;
    case PosicionD: alarmState(); 
                    break;
    default:        Serial.println("state Unknown"); 
                    break;
  }
  stateMachine.Update();
}
