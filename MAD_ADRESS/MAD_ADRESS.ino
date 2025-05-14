/*
    PROGRAMA PARA IDENTIFICAR LA MAC DE LAS PLACAS ESP32
*/
#if defined(ESP32)
    #include "WiFi.h"
#else
    #error This board is not supported
#endif
void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    Serial.println(WiFi.macAddress());
}
void loop(){
  //NADA AQUÍ
}
