#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SDA_PIN 21                  //SALIDA DEL ESP32 PARA EL MODULO I2C
#define SDA_PIN 22                  //SALIDA DEL ESP32 PARA EL MODULO I2C
#define I2C_SLAVE_ADDR 0X04         //LIBRERÍA NECESARIA PARA EL MODULO I2C
LiquidCrystal_I2C lcd(0x27,16,2);   //DIRECCIÓN DEL LCD

//DEFINIR PINES DE ENTRADA DE LOS BOTONES
const int buttonPin1 = 2;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
const int buttonPin4 = 34;
const int buttonPin5 = 35;

//DEFINIR LOS PINES DE SALIDA DE LOS LEDS
const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 14;
const int ledPin4 = 27;
const int ledPin5 = 26;

//INICIALIZAMOS LOS BOTONES CON UNA ENTRADA DE CERO
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;

void setup() {
  //DEFINIMOS SALIDAS
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);

  //DEFINIMOS ENTRADAS
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);

  //ARGUMENTOS QUE SE MUESTRAN EN PANTALLA QUE MUESTRA EL LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA
  lcd.print("SIST. EMBEBIDOS");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA
  lcd.print("6TO SEMESTRE");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA
  lcd.print("EQUIPO 1 - RL9");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD}
  lcd.setCursor(2,0);     //POCISIONA
  lcd.print("INTEGRANTE 1");
  lcd.setCursor(5,1);     //POCISIONA
  lcd.print("Alfonso");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(2,0);     //POCISIONA
  lcd.print("INTEGRANTE 2");
  lcd.setCursor(5,1);     //POCISIONA
  lcd.print("Uriel");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(2,0);     //POCISIONA
  lcd.print("INTEGRANTE 3");
  lcd.setCursor(5,1);     //POCISIONA
  lcd.print("Diego");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(2,0);     //POCISIONA
  lcd.print("INTEGRANTE 4");
  lcd.setCursor(5,1);     //POCISIONA
  lcd.print("Alexis");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(4,0);     //POCISIONA
  lcd.print("SENSORES");
  delay (2000);
  
  lcd.clear();            //LIMPIAR LCD
  lcd.setCursor(0,0);     //POCISIONA
}
void loop() {
  //LEER EL ESTADO DE LOS SENSORES
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);

  //EVALUAR SENSOR 1
  if (buttonState1 == HIGH) {
    digitalWrite(ledPin1, HIGH);
    lcd.clear();                    //LIMPIA EL LCD
    lcd.print("SENSOR 1 . . .");    //IMPRIME
  } else {
    digitalWrite(ledPin1, LOW);     //APAGA EL LED
  }

  //EVALUAR SENSOR 2
  if (buttonState2 == HIGH) {
    digitalWrite(ledPin2, HIGH);
    lcd.clear();                    //LIMPIA EL LCD
    lcd.print("SENSOR 2 . . .");    //IMPRIME
  } else {
    digitalWrite(ledPin2, LOW);     //APAGA EL LED
  }

  //EVALUAR SENSOR 3
  if (buttonState3 == HIGH) {
    digitalWrite(ledPin3, HIGH);
    lcd.clear();                    //LIMPIA EL LCD
    lcd.print("SENSOR 3 . . .");    //IMPRIME
  } else {
    digitalWrite(ledPin3, LOW);     //APAGA EL LED
  }

  //EVALUAR SENSOR 4
  if (buttonState4 == HIGH) {
    digitalWrite(ledPin4, HIGH);
    lcd.clear();                    //LIMPIA EL LCD
    lcd.print("SENSOR 4 . . .");    //IMPRIME
  } else {
    digitalWrite(ledPin4, LOW);     //APAGA EL LED
  }

  //EVALUAR SENSOR 5
  if (buttonState5 == HIGH) {
    digitalWrite(ledPin5, HIGH);
    lcd.clear();                    //LIMPIA EL LCD
    lcd.print("SENSOR 5 . . .");    //IMPRIME
  } else {
    digitalWrite(ledPin5, LOW);     //APAGA EL LED
  }

  //SI NINGUNO DE LOS BOTONES ESTÁN PRESIONADOS ENTONCES MOSTRAMOS UN MENSAJE DE ESPERA
  if (buttonState1 == LOW && buttonState2 == LOW && buttonState3 == LOW && buttonState4 == LOW && buttonState5 == LOW) {
    lcd.clear();
    lcd.print("Esperando . . .");
  }
}
