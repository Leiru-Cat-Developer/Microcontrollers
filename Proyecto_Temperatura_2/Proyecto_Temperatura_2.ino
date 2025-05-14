//ADC1_4
const int sensorPin = 32;
int sensorValor = 0;
int valor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValor = analogRead(sensorPin);
  valor = map(sensorValor,0,4095,500,1500);
  Serial.print("Sensor = ");
  Serial.println(valor, DEC);
  delay(100);
}
