#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd {0,1,5,4,3,2};//RS EV D5 D6 D7 D8

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

//VARIABLES GLOBALES

//Conexiones de pines para el led 
int redPin = 32;
int greenPin = 34;
int bluePin = 36;

//Variables globales para el sistema de seguridad
int pos=0;
int atmps = 1;

//Contrasenia del sistema
char secretCode[7] = {'8','7','6','1','8','9','#'};
char enterCode[7]={'0','0','0','0','0','0','#'};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    
    lcd.begin(16, 2);
    lcdSetPrint(0,0,"   Welcome!  ");
    delay(3000);
    lcd.clear();
}

void loop(){
    sistemaSeguridad();
}

void sistemaSeguridad(){
    if(atmps < 4){ 
        ingresoContrasenia();
    }
    else{
        sistemaBloqueado();
    }
}

void ingresoContrasenia(){
  lcdSetPrint(0,0,"PASSWORD:");
  char key = keypad.getKey();
  if(key){
    if(key=='#'||pos==7){
      verificar(enterCode);
    }else{
      leerContrasenia(key); 
    }
  }  
}
void leerContrasenia(char key){
  lcdSetPrint(pos,1,"*");
  enterCode[pos]=key;
  pos++;
}
void verificar(char charac[]){
    for(pos=0;pos<7;pos++){
      if(charac[pos]!=secretCode[pos]){
        contraseniaIncorrecta();
        return;
      }
    }
    contraseniaCorrecta();
}
void contraseniaIncorrecta(){
  lcdSetPrint(0,1,"INCORRECTA!");
  enterCode[6]='#';
  ledCon(255,120,0,2000); //Led en naranja y espera 2 segundos
  if(atmps<3){
    lcdSetPrint(0,1," TRY AGAIN!");
    ledCon(0,0,0,2000); //Led sin encender y...
    }
  lcd.clear();
  pos = 0;
  atmps++;
}

void contraseniaCorrecta(){
  lcdSetPrint(0,1,"CORRECTO");
  delay(1500);
  lcd.clear();
  lcdSetPrint(0,0,"BIENVENIDO");
  ledCon(0,255,0,2000);  //Verde
  ledCon(0,0,0,2000);
  sistemaDesbloqueado();
  lcd.clear();
}
void sistemaBloqueado(){
  lcdSetPrint(0,0," SYS BLOQUEADO");
  ledCon(255,0,0,5000);  //Rojo
  ledCon(0,0,0,2000);
  pos = 0;
  atmps = 0;
  lcd.clear();
}
void sistemaDesbloqueado(){
    ledCon(120,0,255,1000);
    ledCon(255,0,120,1000);
    ledCon(255,0,255,1000);
    ledCon(255,0,120,1000);
    ledCon(255,0,255,1000);
    ledCon(255,0,120,1000);
    ledCon(120,0,255,1000);
    ledCon(255,0,255,1000);
    ledCon(255,0,120,1000);
    ledCon(120,0,255,1000);
    pos=0;
    atmps=1;
}
void setColor(int red, int green, int blue){
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);
}
void ledCon(int r, int g, int b, int time_ms){
  setColor(r,g,b);
  delay(time_ms);
}
void lcdSetPrint(int c, int f, char mensaje[]){
  lcd.setCursor(c, f);
  lcd.print(mensaje);
}
