//ADC1_4
#define ledVerde 13
#define ledRojo 14

//VARIABLE PARA ALMACENAR LA LECTURA EN DIGITAL DEL ADC
float temperatura;
int tempPin = 32;

void setup() {
  pinMode(ledVerde,OUTPUT);
  pinMode(ledRojo,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  temperatura = analogRead(tempPin);
  temperatura *= 0.48828125;
  temperatura *= 0.0805860805860;
  Serial.print("TEMPERATURA = ");
  Serial.print(temperatura);
  Serial.print(" C");
  Serial.println();
  if((temperatura >= 22)&&(temperatura < 28)){
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, HIGH);
  }else if(temperatura >= 28){
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
  }else{
    digitalWrite(ledRojo, LOW);
    digitalWrite(ledVerde, LOW);
  }
  delay(500);
}
