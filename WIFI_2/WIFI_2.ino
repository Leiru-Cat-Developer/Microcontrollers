//IMPORTAR LAS BIBLIOTECAS REQUERIDAS PARA HACER LA CONEXION

#include "WiFi.h"
#include "ESPAsyncWebSrv.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>


//REEMPLAZAR CON LAS CREDENCIALES DE LA RED LOCAL A LA QUE ESTA CONECTADA

const char* ssid = "Wi-Fi IPN";   //PONER NOMBRE DE LA RED
const char* password = "";        //PONER PASSWORD DE LA RED

#define DHTPIN 4          //PIN DIGITAL CONECTADO AL SENSOR "DHT"
#define DHTTYPE DHT11     //TIPO DE SENSOR

DHT dht(DHTPIN, DHTTYPE);

// Crear objeto AsyncWebServer en el puerto 80
AsyncWebServer server(80);

String readDHTTemperature() {
  // Las lecturas del sensor también pueden tener hasta 2 segundos de retraso (es un sensor muy lento)
  // Lee la temperatura como Celsius (el valor predeterminado)
  float t = dht.readTemperature();
  // Lee la temperatura en grados Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Verifique si alguna lectura falló y salga temprano (para volver a intentarlo).
  if (isnan(t)) {    
    Serial.println("No se pudo leer desde el sensor DHT!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // as lecturas del sensor también pueden tener hasta 2 segundos de retraso (es un sensor muy lento)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("No se pudo leer desde el sensor DHT!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 DHT Server</h2>
  <p>
   <h2>SISTEMAS EMBEBIDOS</h2>
  <p>
   <h2>UPIICSA - ING. INFORMATICA</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperature</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  dht.begin();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectado a WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
