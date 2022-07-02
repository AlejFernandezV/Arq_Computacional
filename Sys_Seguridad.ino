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
//Pines en donde se conectará el KeyPad
byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

//VARIABLES GLOBALES

//Conexiones de pines para el led 
int redPin = 32;
int greenPin = 34;
int bluePin = 36;

//Variables globales para el sistema de seguridad
int pos=0;      //Variable que controlará la posición en donde se imprimirán los caracteres en el lcd
int atmps = 1;  //Variable que maneja el número de intentos

//Contrasenia del sistema
char secretCode[7] = {'8','7','6','1','8','9','#'};

//Vector donde se guardará la contrasenia ingresada
char enterCode[7]={'0','0','0','0','0','0','#'};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Inicialización de los componentes (Led RGB y KeyPad)
void setup(){
    
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.print ("   Welcome!  ");
    delay(3000);
    lcd.clear();
}


void loop(){
    sistemaSeguridad();
}

void sistemaSeguridad(){
    //Verifica el numero de intentos
    if(atmps < 4){ 
        //Verifica cuantos caracteres se han colocado en el vector que guardará la contraseña ingresada
        if(pos < 8){
            ingresoContrasenia();
        }
        else{
          contraseniaIncorrecta();
        }
    }
    else{
        sistemaBloqueado();
    }
}

//Recibe los caracteres de la contraseña para luego compararlos si son verdaderos
void ingresoContrasenia(){
  lcd.setCursor(0,0);
  lcd.print("PASSWORD:");
    char key = keypad.getKey();
    if(key){
      //Cuando se ingrese el "#" verficiará el codigo ingresado
      if(key=='#'){
        verificar(enterCode);
      //Si no se ha ingresado el "#" leerá e iprimirá un "*" por cada dígito ingresado
      }else{
        lcd.setCursor(pos,1);
        lcd.print('*');
        enterCode[pos] =key;
        pos++;
      }
    }  
}

//Verifica si lo ingresado en el vector coincide con la contraseña pre-establecida
void verificar(char charac[]){
    for(pos=0;pos<7;pos++){
      if(charac[pos]!=secretCode[pos]){
        contraseniaIncorrecta();
        return;
      }
    }
    contraseniaCorrecta();
}


//Proceso al equivocarse de contraseña 
void contraseniaIncorrecta(){
    lcd.setCursor(0,1);
    lcd.print("INCORRECTA!");
    setColor(255,120,0);    //Naranja
    delay(2000);
    if(atmps<3){
      lcd.setCursor(0,1);
      lcd.print("TRY AGAIN!");
      setColor(0,0,0);       
      delay(2000);
      }
    lcd.clear();
    pos = 0;
    atmps++;
}

//Proceso al ingresar la contraseña correctamente
void contraseniaCorrecta(){
    lcd.setCursor(0,1);
    lcd.print("CORRECTO");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BIENVENIDO");
    setColor(0,255,0);      //Verde
    delay(2000);
    setColor(0,0,0);       
    delay(2000);
    sistemaDesbloqueado();
    lcd.clear();
}

//Proceso del bloqueo del sistema al superar los intentos permitidos(3) 
//para ingresar de manera correcta la contraseña
void sistemaBloqueado(){
    lcd.setCursor(0,0);
    lcd.print("SYS BLOQUEADO");
    //Al bloquear el sistema devolverá la posicion de impresión en el lcd a 0 al igual que los intentos  
    pos = 0;
    atmps = 0;
    setColor(255,0,0);      //Rojo
    delay(5000);            // <--- Tiempo en el cual el sistema estará bloqueado
    lcd.clear();            //Borra lo que esté impreso en el lcd
}

////Proceso que nos indica que ya se desbloqueó el sistema.
void sistemaDesbloqueado(){
    setColor(120,0,255);
    delay(1000);
    setColor(255,0,120);
    delay(1000);
    setColor(255,0,255);
    delay(1000);
    setColor(255,0,120);
    delay(1000);
    setColor(255,0,255);
    delay(1000);
    setColor(255,0,120);
    delay(1000);
    setColor(255,0,255);
    delay(1000);
    setColor(255,0,120);
    delay(1000);
    setColor(255,0,255);
    delay(1000);
    setColor(255,0,120);
    delay(1000);
}

//Seteo de la función para darle color al led
void setColor(int red, int green, int blue){
  analogWrite(redPin,red);
  analogWrite(greenPin,green);
  analogWrite(bluePin,blue);
}
