// TX
#define RXD2 16
#define TXD2 17
int Sensor = 32;        //Puerto analógico cad1-c4 para el sensor LM35
int ValorSensor = 0;    //Variable de almacenamiento de datos del sensor
float Temperatura = 0;  //Variable para el cálculo de temperatura

int Grados_Cent;        //Variable para grados Centígrados
int Grados_Fahr;        //Variable para grados Fahrenheit
int Grados_Kelv;        //Variable para grados Kelvin

int Rojo = 13;          //Puerto digital 10 para LED rojo
int Verde = 12;          //Puerto digital 9 para LED verde
int Amarillo = 14;       //Puerto digital 8 para LED amarillo

unsigned long Tiempo_Tx;  //variable para los tiempos de transmisión

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);   //Velocidad de transmisión 115200 bps
Serial2.begin(115200, SERIAL_8N1,RXD2,TXD2);//Serial Por2
delay(1000);            //Retardo
//Configuración de puertos digitales como salidas
pinMode(Rojo,OUTPUT);
pinMode(Verde,OUTPUT);
pinMode(Amarillo,OUTPUT);
//Inicialización de los puertos como nivel lógico 0
digitalWrite(Rojo, LOW);
digitalWrite(Verde, LOW);
digitalWrite(Amarillo, LOW);

Tiempo_Tx = millis();     //leer tiempos de inicio de programa

}

void loop() {
  // put your main code here, to run repeatedly:
ValorSensor = analogRead(Sensor);               //Lectura del sensor LM35
Temperatura = (ValorSensor *3.3/4095.0)/0.01;             //Cálculo de temperatura

Grados_Cent = (int)Temperatura;                 //grados centígrados
Grados_Fahr = (int)(Grados_Cent * 1.8) + 32;    //grados Fahrenheit que se suman a centigrados 32 grados
Grados_Kelv = (int)(Grados_Cent + 273.15);      //grados Kelvin se multiplica por grados centigrados 

// Trasmisión de datos
if ((millis()- Tiempo_Tx) > 500) {        //Transmisión en medio segundo
Serial2.print(Grados_Cent);                //Transmisión de grados centígrados
Serial2.print("C");                        //Enviamos la unidad
Serial2.print(Grados_Fahr);                //Transmisión de grados Fahrenheit
Serial2.print("F");                        //Enviamos la unidad
Serial2.print(Grados_Kelv);                //Transmisión de grados Kelvin
Serial2.println("K");                        //Enviamos la unidad
Tiempo_Tx = millis();                     //Tiempo de actualización
}

//Recepción de datos
if (Serial2.available() >0){
  int datos = Serial2.read();              //Lectura de datos
  if(datos == 'a'){                       //Temperatura alta
    digitalWrite(Rojo, HIGH);             //Encendido del LED rojo
    digitalWrite(Verde, LOW);
    digitalWrite(Amarillo, LOW);
  }
   if(datos == 'b'){                      //Temperatura baja
    digitalWrite(Rojo, LOW);              //Encendido del LED amarillo
    digitalWrite(Verde, LOW);
    digitalWrite(Amarillo, HIGH); 
}
  if(datos == 'n'){                       //Temperatura normal
    digitalWrite(Rojo, LOW);              ////Encendido del LED verde
    digitalWrite(Verde, HIGH);
    digitalWrite(Amarillo, LOW); 
}
}
}
