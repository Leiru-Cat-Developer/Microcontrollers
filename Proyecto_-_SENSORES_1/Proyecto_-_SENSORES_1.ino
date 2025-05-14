//DEFINIR PINES DE ENTRADA DE LOS BOTONES
const int buttonPin1 = 2;
const int buttonPin2 = 4;
const int buttonPin3 = 5;

//DEFINIR LOS PINES DE SALIDA DE LOS LEDS
const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 14;

//INICIALIZAMOS LOS BOTONES CON UNA ENTRADA DE CERO
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup() {
  //DEFINIMOS SALIDAS
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  //DEFINIMOS ENTRADAS
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  //BOTÓN UNO
  if(buttonState1 == HIGH){
    //PRENDER
    digitalWrite(ledPin1, HIGH);
  }
  else{
    //APAGAR
    digitalWrite(ledPin1, LOW);
  }

  //BOTÓN DOS
  if(buttonState2 == HIGH){
    //PRENDER
    digitalWrite(ledPin2, HIGH);
  }
  else{
    //APAGAR
    digitalWrite(ledPin2, LOW);
  }

  //BOTÓN TRES
  if(buttonState3 == HIGH){
    //PRENDER
    digitalWrite(ledPin3, HIGH);
  }
  else{
    //APAGAR
    digitalWrite(ledPin3, LOW);
  }
}

/*

                      PARTE DEL PROGRAMA EN DONDE TENEMOS QUE IMPLEMENTAR EL LCD

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SDA_PIN 21
#define SDA_PIN 22
#define I2C_SLAVE_ADDR 0X04
LiquidCrystal_I2C lcd(0x27,16,2);   //DIRECCIÓN DEL LCD

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("SIST. EMBEBIDOS");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(3,1);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("6TO SEMESTRE");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("EQUIPO 1");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("RL9");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("Alfonso");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("Uriel");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("Diego");
  delay (2000);
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA LA PRIMERA LETRA DESDE DEL SEGMENTO 0 EN LINEA 0
  lcd.print("Alexis");
  delay (2000);
}
*/
