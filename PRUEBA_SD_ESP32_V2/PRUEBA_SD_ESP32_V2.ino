/* PLACA     ESP32
 * 3.3       3.3
 * CS        GPIO5
 * MOSI      GPIO23
 * CLK       GPIO18
 * MISO      GPIO19
 * GND       GND
 */

#include<SD.h>
#include<SPI.H>
#include<FS.h>

#define SD_CS_PIN 5

#define SCK 18
#define MISO 19
#define MOSI 23

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
SPIClass spi = SPIClass(VSPI);
  spi.begin(SCK, MISO,MOSI,SD_CS_PIN);
if (!SD.begin(SD_CS_PIN))// establecemos la comunicacion con la tarjeta 5
{
  Serial.println("Error al inicializar la Tarjeta SD");
  return;
}
  Serial.println("Tarjeta SD inicializada correctamente");
File myFile = SD.open("/sisem.txt",FILE_WRITE);
//File myFile = SD.open("/test.txt",FILE_WRITE);
if(!myFile)
{
  Serial.println("Error al abrir el archivo");
  return;
}
myFile.println("SISTEMAS EMBEBIDOS");
myFile.println("- ALFONSO");
myFile.println("- DIEGO");
myFile.println("- YASHARET ALEXIS");
myFile.println("- URIEL");

myFile.close();

 myFile = SD.open("/sisem.txt",FILE_READ);
Serial.println("Esto es lo que leo de la tarjeta SD");
if(!myFile){
   Serial.println("ERROR AL ABRIR EL ARCHIVO");
   return;
}
while(myFile.available()){
    Serial.write(myFile.read());
  }
  myFile.close();
}


void loop() {
  // put your main code here, to run repeatedly:

}
