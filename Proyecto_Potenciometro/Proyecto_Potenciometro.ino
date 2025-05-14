//ADC1_4
const  int potenciometro = 32;

//VARIABLE PARA ALMACENAR LA LECTURA EN DIGITAL DEL ADC
int lectura;

void setup() {
  Serial.begin(9600);
  //analogReadResolution(); //DE 9 - 12 bit's
}

void loop() {
  lectura = analogRead(potenciometro);
  /*
    BINARIO         - BIN
    HEXADECIMAL     - HEX
    OCTAL           - OCT
  */
  Serial.println(lectura, BIN);
  delay(50);
}
