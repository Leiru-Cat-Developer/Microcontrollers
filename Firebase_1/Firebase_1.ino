#include <WiFi.h>
#include <Laika_FirebaseESP32.h>

//#include <ESP32Firebase.h>          //LIBRERIA ORIGINAL

#define FIREBASE_HOST "casaprueba1-96304-default-rtdb.firebaseio.com/"  //DATABASE URL SIN https:// y DEPENDE SIN "/" AL FINAL
#define FIREBASE_AUTH "V1naXVSFbNJICAbi2qdLyao1HXWpPU4R5Dk4pQ85"        //PASSWORD DE LA BASE DE DATOS

#define WIFI_SSID "Wi-Fi IPN"     //NOMBRE DE LA RED 2.4 GHz
#define WIFI_PASSWORD ""          //CONTRASEÑA DE LA RED

#define RELEFOCO 13              //FOCO
#define RELEMDERECHA 14          //MOTOR DERECHA
#define RELEMIZQUIERDA 27        //MOTOR IZQUIERDA
#define RELEACTUADORABRIR 26     //ACTUADOR ABRIR
#define RELEACTUADORCERRAR 32    //ACTUADOR CERRAR

String foco1;
String motor1;
String motor2;
String actuador1;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("----- REALIZANDO CONEXION WIFI -----");
  Serial.println();
  Serial.println();
  Serial.print("CONECTANDO");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(" . ");
    delay(500);
  }
  
  Serial.println();
  Serial.println();
  Serial.print("CONEXION WIFI EXITOSA");
  Serial.println();
  Serial.println();
  Serial.print("DIRECCION IP: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  Serial.println();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  pinMode(RELEFOCO, OUTPUT);
  pinMode(RELEMDERECHA, OUTPUT);
  pinMode(RELEMIZQUIERDA, OUTPUT);
  pinMode(RELEACTUADORABRIR, OUTPUT);
  pinMode(RELEACTUADORCERRAR, OUTPUT);
}

void loop() {
  if (Firebase.failed()) {
    Serial.print("ERROR EN BASE DE DATOS (FIREBASE): ");
    Serial.print(Firebase.error());
    Serial.println();
    Serial.println();
  }
  
  foco1 = Firebase.getString("/CasaPrueba1/foco1");                         //FOCO
  //CONDICIONES PARA ENCENDER Y APAGAR EL FOCO
  if (foco1 == "ENCENDER FOCO") {
    
    Serial.println("FOCO ENCENDIDO");
    digitalWrite(RELEFOCO , HIGH);
    
  } else if (foco1 == "APAGAR FOCO") {
    
    Serial.println("FOCO APAGADO");
    digitalWrite(RELEFOCO , LOW);
  
  }

  motor1 = Firebase.getString("/CasaPrueba1/motor1");                       //MOTOR DERECHA
  //CONDICIONES PARA ACTIVAR EL MOTOR DERECHO
  if (motor1 == "ENCENDER MOTOR DERECHO") {
    
    Serial.println("MOTOR GIRANDO HACIA LA DERECHA");
    digitalWrite(RELEMIZQUIERDA , LOW);               //PREVENIMOS EN CASO DE ENCENDIDO
    digitalWrite(RELEMDERECHA , HIGH);
    
  } else if (motor1 == "APAGAR MOTOR DERECHO") {
    
    Serial.println("MOTOR DERECHO APAGADO");
    digitalWrite(RELEMDERECHA , LOW);
  
  }

  motor2 = Firebase.getString("/CasaPrueba1/motor2");                       //MOTOR IZQUIERDA
  //CONDICIONES PARA ACTIVAR EL MOTOR IZQUIERDO
  if (motor2 == "ENCENDER MOTOR IZQUIERDO") {
    
    Serial.println("MOTOR IZQUIERDO ENCENDIDO");
    digitalWrite(RELEMDERECHA , LOW);                 //PREVENIMOS EN CASO DE ENCENDIDO
    digitalWrite(RELEMIZQUIERDA , HIGH);
  
  } else if (motor2 == "APAGAR MOTOR IZQUIERDO") {
  
    Serial.println("MOTOR IZQUIERDA APAGADO");
    digitalWrite(RELEMIZQUIERDA , LOW);
  
  }

  actuador1 = Firebase.getString("/CasaPrueba1/actuador1");                 //ACTUADOR ABR - CERR
  //CONDICIONES PARA ABRIR Y CERRAR EL ACTUADOR
  if (actuador1 == "ABRIR PUERTA") {
    
    Serial.println("ACTUADOR ABIERTO");
    digitalWrite(RELEACTUADORABRIR , HIGH);
    digitalWrite(RELEACTUADORCERRAR , LOW);
    delay(1000);
    digitalWrite(RELEACTUADORABRIR , LOW);
    digitalWrite(RELEACTUADORCERRAR , LOW);
  
  } else if (actuador1 == "CERRAR PUERTA") {
    
    Serial.println("ACTUADOR CERRADO");
    digitalWrite(RELEACTUADORCERRAR , HIGH);
    digitalWrite(RELEACTUADORABRIR , LOW);
    delay(1000);
    digitalWrite(RELEACTUADORCERRAR , LOW);
    digitalWrite(RELEACTUADORABRIR , LOW);
  
  }else if(actuador1 == "PUERTA NEUTRO"){
    
    Serial.println("ACTUADOR APAGADO");
    digitalWrite(RELEACTUADORABRIR , LOW);
    digitalWrite(RELEACTUADORCERRAR , LOW);  
  
  }

  Serial.println();                           //ESPACIO PARA EVITAR QUE SE JUNTEN PALABRAS
}
