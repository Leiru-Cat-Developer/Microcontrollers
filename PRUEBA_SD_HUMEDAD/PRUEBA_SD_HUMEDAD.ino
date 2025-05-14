#include "arduino.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"
#include "DHT.h"

#define SD_CS_PIN 5

DHT dht(32, DHT11);

File archivoEQ1;

void setup() {
  Serial.begin(115200);

  dht.begin();
  if(!SD.begin(SD_CS_PIN)){
    Serial.println("ERROR AL INICIALIZAR LA TARJETA SD");
    return;
  }
  Serial.println("TARJETA SD INICIALIZADA CORRECTAMENTE");
}

void loop() {
  delay(2000);  //ESPERA 2 SEGUNDOS ENTRE LECTURAS
  
  //LEER HUMEDAD Y TEMPERATURA
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  //COMPROBAR SI LAS LECTURAS SON VALIDAS
  if(isnan(h) || isnan(t)){
      Serial.println(F("ERROR AL LEER SENSOR DHT11"));
  }else{
    //MOSTRAR LAS LECTURAS EN EL MONITOR SEIAL
    Serial.println(F("HUMEDAD: "));
    Serial.print(h);
    Serial.print(F("% ... TEMPERATURA: "));
    Serial.print(t);
    Serial.print(F("°C"));
    Serial.println();                       //ENTER  
  }
  File archivoEQ1 = SD.open("/archivoTH.txt",FILE_WRITE);
  if(!archivoEQ1){
      Serial.println("ERROR AL ABRIR EL ARCHIVO");
      return;
  }

  //EN LA SIGUIENTE LINEA DEBE DE ESCRIBIR EN LA TARJETA SD

  archivoEQ1.println(t);
  archivoEQ1.println(h);
  archivoEQ1.close();

  Serial.println("DATOS ESCRITOS EN EL ARCHIVO");
  archivoEQ1 = SD.open("/archivoTH.txt",FILE_READ);
  if(!archivoEQ1){
      Serial.println("ERROR AL ABRIR EL ARCHIVO");
      return;
  }

  Serial.println("ESTO ES LO QUE LEO DE LA TARJETA SD");
  while(archivoEQ1.available()){
      Serial.write(archivoEQ1.read());
  }
  archivoEQ1.close();
}
