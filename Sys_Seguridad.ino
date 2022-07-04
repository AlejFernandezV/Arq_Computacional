#include <LiquidCrystal.h>
#include <Keypad.h>

//Initialize LiquidCrystal
LiquidCrystal lcd {0,1,5,4,3,2};//Param: RS, EV, D4, D5, D6, D7.

//Initialize Keypad
#define ROWS 4
#define COLS 3
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 24, 26}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Initialize SYSTEM SECURITY variables
int pos=0;
int attempt = 0;
//Password
char secretCode[7] = {'8','7','6','1','8','9','#'};
char enterCode[7]={'0','0','0','0','0','0','#'};

//Pin connection for RGB LED (Always in the POWER field)
#define REDPIN 11
#define GREENPIN 12
#define BLUEPIN 13

void setup(){
  //Initialize RGB LED
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  
  lcd.begin(16, 2);
  lcdSetPrint(0,0,"   Welcome!  ");
  delay(3000);
  lcd.clear();
}
void loop(){
    securitySystem();
}
void securitySystem(){
    if(attempt < 3){ 
        enterPassword();
    }
    else{
        lockSystem();
    }
}
void enterPassword(){
  lcdSetPrint(0,0,"PASSWORD:");
  char key = keypad.getKey();
  if(key){
    if(key=='#'||pos==7){
      check();
    }else{
      readPassword(key); 
    }
  }  
}
void readPassword(char key){
  lcdSetPrint(pos,1,"*");
  enterCode[pos]=key;
  pos++;
}
void check(){
    for(pos=0;pos<7;pos++){
      if(enterCode[pos]!=secretCode[pos]){
        wrongPassword();
        return;
      }
    }
    correctPassword();
}
void wrongPassword(){
  lcdSetPrint(0,1,"WRONG!");
  enterCode[6]='#';
  ledWth(255,120,0,2000); //Orange and wait 2 seconds.
  if(attempt<2){
    lcdSetPrint(0,1," TRY AGAIN!");
    ledWth(0,0,0,2000); //Led turn off...
    }
  lcd.clear();
  pos = 0;
  attempt++;
}
void correctPassword(){
  lcdSetPrint(0,1,"CORRECT...");
  delay(1500);
  lcd.clear();
  lcdSetPrint(0,0,"   WELCOME");
  ledWth(0,255,0,2000);  //Green
  ledWth(0,0,0,2000);
  unlockSystem();
  lcd.clear();
}
void lockSystem(){
  lcdSetPrint(0,0,"SYSTEM LOCKED");
  ledWth(255,0,0,5000);  //Red
  ledWth(0,0,0,2000);
  pos = attempt = 0;
  lcd.clear();
}
void unlockSystem(){
    ledWth(120,0,255,1000);
    ledWth(255,0,120,1000);
    ledWth(255,0,255,1000);
    ledWth(255,0,120,1000);
    ledWth(255,0,255,1000);
    ledWth(255,0,120,1000);
    ledWth(120,0,255,1000);
    ledWth(255,0,255,1000);
    ledWth(255,0,120,1000);
    ledWth(120,0,255,1000);
    pos=attempt=0;
}
void setColor(int red, int green, int blue){
  analogWrite(REDPIN,red);
  analogWrite(GREENPIN,green);
  analogWrite(BLUEPIN,blue);
}
void ledWth(int r, int g, int b, int time_ms){
  setColor(r,g,b);
  delay(time_ms);
}
void lcdSetPrint(int c, int f, char message[]){
  lcd.setCursor(c, f);
  lcd.print(message);
}
