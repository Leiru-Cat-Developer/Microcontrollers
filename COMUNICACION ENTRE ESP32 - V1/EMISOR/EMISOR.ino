#define RXD2 16
#define TXD2 17
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial2.begin(9600, SERIAL_8N1,RXD2,TXD2);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial2.println("Hola soy ESP32");
delay(2000);
}
