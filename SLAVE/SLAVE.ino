/*
      DESTINATARIO (SLAVE)
*/
#include <esp_now.h>
#include <WiFi.h>

int ledPinFoco = 13;

int state = 0;

// TAMBIEN SE REQUIERE EN EL CLIENTE PARA PODER GUARDAR LOS DATOS DIRECTAMENTE

typedef struct temp_humidity {
  float temperature;
  float humidity;
};

// CREA UN STRUCT_MESSAGE LLAMADA "myData"
temp_humidity dhtData;

// FUNCION DE DEVOLUCION DE LLAMADA EJECUTADA CUANDO SE RECIBEN DATOS
void OnRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  
  memcpy(&dhtData, incomingData, sizeof(dhtData));
  
  Serial.print("BYTES RECIBIDOS: ");
  Serial.println(len);
  Serial.print("TEMPERATURA: ");
  Serial.println(dhtData.temperature);
  Serial.print("HUMEDAD: ");
  Serial.println(dhtData.humidity);
}

void setup() {
  // INICIALIZAR MONITOR SERIE
  Serial.begin(115200);
  
  // CONFIGURAR EL DISPOSITIVO COMO ESTACION WI-FI
  WiFi.mode(WIFI_STA);
  // INICIAR ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("HUBO UN ERROR AL INICIALIZAR ESP-NOW . . .");
    return;
  }
  
  // UNA VEZ INICIALIZADO EL PROTOCOLO ESP-NOW, REGISTRAREMOS LA FUNCION DE DEVOLUCION DE LLAMADA
  // PARA PODER REACCIONAR CUANDO LLEGA UN PAQUETE CASE EN TIEMPO REAL SIN AGRUPAR TODOS LOS BUCLES
  esp_now_register_recv_cb(OnRecv);



  pinMode(ledPinFoco, OUTPUT);
   
  digitalWrite(ledPinFoco, LOW);
}

void loop() {
  if(dhtData.temperature == 1){
      state = 1;
  }else if(dhtData.temperature == 0){
      state = 0;
  }
  if(state == 1){
      digitalWrite(ledPinFoco,HIGH);
  }else if(state == 0){
      digitalWrite(ledPinFoco,LOW);
  }
}
