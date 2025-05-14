//ADC1_4
const int LM35 = 32;

//VARIABLE PARA ALMACENAR LA LECTURA EN DIGITAL DEL ADC
float temperatura;

void setup() {
  Serial.begin(9600);
}

void loop() {
  temperatura = (float(analogRead(LM35))*3.3/4095.0)/0.01;
  Serial.print("TEMPERATURA = ");
  Serial.print(temperatura);
  Serial.print(" C");
  Serial.println();
  delay(500);
}
