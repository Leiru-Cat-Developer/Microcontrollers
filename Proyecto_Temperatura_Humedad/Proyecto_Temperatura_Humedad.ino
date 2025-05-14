#include <DHT.h>
DHT dht(32,DHT11);

void setup() {
  dht.begin();
  delay(2000);
  Serial.begin(9600);
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C ");
  Serial.println();           //ESPACIO VACIO
  Serial.print("HUMEDAD: ");
  Serial.print(humidity);
  Serial.print(" % ");
  delay(500);
}
