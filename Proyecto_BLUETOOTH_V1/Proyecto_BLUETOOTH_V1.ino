#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#define SDA_PIN 21
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x04
LiquidCrystal_I2C lcd(0x27,16,2);

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED)||!defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif
BluetoothSerial SerialBT;

int ledPinFoco = 13;

int ledPinActCer = 15;
int ledPinActAbr = 4;
int ledPinMotIzq = 18;
int ledPinMotDer = 19;

int state = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32lasputisueltas");
  Serial.println(" el dispositivo esta listo");
  
pinMode(ledPinFoco, OUTPUT);
pinMode(ledPinActCer, OUTPUT);
pinMode(ledPinActAbr, OUTPUT);
pinMode(ledPinMotIzq, OUTPUT);
pinMode(ledPinMotDer, OUTPUT);

digitalWrite (ledPinFoco, LOW);
digitalWrite (ledPinActCer, LOW);
digitalWrite (ledPinActAbr, LOW);
digitalWrite (ledPinMotIzq, LOW);
digitalWrite (ledPinMotDer, LOW);

  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("sis. embebidos");
  lcd.setCursor(0,1);
  lcd.print("ing. informatica");
  delay (2000);
  lcd.clear();
  
  lcd.setCursor(1,0);
  lcd.print("comunicacion");
  lcd.setCursor(1,1);
  lcd.print("bluetooth");
  delay (3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialBT.available()) {
    char Mensaje = SerialBT.read();


    //FOCO
  if (Mensaje == 'P') {
    digitalWrite (ledPinFoco, HIGH);
    lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("pren. foco");
  delay (500);
   Mensaje = 0;  
  }
   if (Mensaje == 'A') {
    digitalWrite (ledPinFoco, LOW);
      lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("apag. foco");
  delay (500);
    Mensaje = 0;
  }
  
  
  //ACTUADOR
  if (Mensaje == 'O') {
    digitalWrite (ledPinActCer, LOW);
    digitalWrite (ledPinActAbr, HIGH);
      lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("abriendo . . .");
  delay
  (500);
    Mensaje = 0;
    digitalWrite (ledPinActAbr, LOW);
  }
  
  if (Mensaje == 'C') {
    digitalWrite (ledPinActCer, HIGH);
    digitalWrite (ledPinActAbr, LOW);
      lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("cerrando . . .");
  delay (500);
    Mensaje = 0;
    digitalWrite (ledPinActCer, LOW);
  }
  


  //MOTOR
  if (Mensaje == 'D') {
    digitalWrite (ledPinMotIzq, LOW);
    digitalWrite (ledPinMotDer, HIGH);
      lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("derecha . . .");
  delay (500);
    Mensaje = 0;
  }

  if (Mensaje == 'I') {
    digitalWrite (ledPinMotIzq, HIGH);
    digitalWrite (ledPinMotDer, LOW);
      lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("izquierda . . .");
  delay (500);
    Mensaje = 0;
  }

  if (Mensaje == 'S') {
    digitalWrite (ledPinMotIzq, LOW);
    digitalWrite (ledPinMotDer, LOW);
      lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("deteniendo . . .");
  delay (500);
    Mensaje = 0;
  }
  }
}
