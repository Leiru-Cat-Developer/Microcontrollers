/*
      REMITENTE (MASTER)
*/
#include <esp_now.h>
#include <WiFi.h>

// ESTABLECER LA DIRECCION MAC ESCLAVO - AQUI VA LA DIRECCION MAC DEL ESCLAVO
uint8_t slaveAddress[] = {0xCC, 0xDB, 0xA7, 0x13, 0xB9, 0xD0};

// ESTRUCTURA PARA GUARDAR LOS DATOS DE TEMPERATURA Y HUMEDAD DE UN SENSOR DHT
typedef struct temp_humidity {
  float temperature;
  float humidity;
};

// CREAR UN STRUCT_MESSAGE LLAMADO "MyData"
temp_humidity dhtData;

// DEVOLUCION DE LLAMADA PARA TENER UN SEGUIMIENTO DE LOS MENSAJES ENVIADOS
void OnSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nENVIAR ESTADO DEL MENSAJE:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "ENVIADO CORRECTAMENTE" : "ENVIO FALLIDO");
}
 
void setup() {
  // INICIAR MONITOR SERIAL
  Serial.begin(115200);
 
  // CONFIGURAR EL DISPOSITIVO COMO ESTACION WI-FI
  WiFi.mode(WIFI_STA);
  
  // INICIAR ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("HUBO UN ERROR AL INICIALIZAR ESP-NOW");
    return;
  }
  
  //REGISTRAREMOS LA FUNCION DE DEVOLUCION DE LLAMADA PARA RESPONDER AL EVENTO
  esp_now_register_send_cb(OnSent);
  
  // REGISTRAR EL ESCLAVO
  esp_now_peer_info_t slaveInfo = {};
  memcpy(slaveInfo.peer_addr, slaveAddress, 6);
  slaveInfo.channel = 0;  //**
  slaveInfo.encrypt = false;
  
  // AÑADIR ESCLAVO        
  if (esp_now_add_peer(&slaveInfo) != ESP_OK){
    Serial.println("HUBO UN ERROR AL REGISTRAR EL ESCLAVO");
    return;
  }
}

void loop() {
  // ESTABLECER VALORES PARA ENVIAR
  // PARA SIMPLIFICAR EL CODIGO SIMPLEMENTE CONFIGURAREMOS DOS FLOTANTES Y LO ENVIAMOS
  dhtData.temperature = 1;
  dhtData.humidity = 0;
  // Es hora de enviar el mensaje a través de ESP-NOW
  esp_err_t result = esp_now_send(slaveAddress, (uint8_t *) &dhtData, sizeof(dhtData));
   
  if(Serial.available()){
    char Mensaje = Serial.read();
    if(Mensaje == 0){
        dhtData.temperature = 0;
    }else if(Mensaje == 1){
        dhtData.temperature = 1;
    }
    delay(3000);
  }
}
