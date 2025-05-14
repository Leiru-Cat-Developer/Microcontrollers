 //RX
  //LiquidCrystal Library 

// P27 -> D7  B_Menos
// P14 -> D6
// P12 -> D5
// P13 -> D4
// P4 -> E
// P2 -> RS
#define RXD2 16
#define TXD2 17
#include <LiquidCrystal.h>                  //Librería LCD
 LiquidCrystal lcd(2, 4, 5, 18, 19, 21);      //configuración de puertos
char datos[13];                             //Variable array para capturar datos de llegada
int posicion = 0;                           //Variable de posición para datos de llegada

char *resultado = NULL;                     //Variable de segmentación de datos 
char separador[] = "CFK";                   //Variable separadora de datos 
int valores[] = {0,0,0};                    //Variable para almacenar los datos segmentados
int Grados_Cent;                      //Variable para grados Centígrados
int Grados_Fahr;                      //Variable para grados Fahrenheit
int Grados_Kelv;                      //Variable para grados Kelvin

unsigned long Tiempo_LCD;             //Variable de tiempo para impresión de datos
unsigned long Tiempo_Tx;              //Variable de tiempo para transmisión de datos

void setup() {
lcd.begin(16, 2);                   //Inicio de pantalla LCD 16x2               
Serial2.begin(115200, SERIAL_8N1,RXD2,TXD2);//Velocidad de transmisión 115200 bps
delay(1000);                        //Retardo
Tiempo_LCD = millis();              //leer tiempos de inicio para LCD
Tiempo_Tx = millis();               //leer tiempos de inicio para Tx

}

void loop() {
  // put your main code here, to run repeatedly:
boolean segmentacion;
//Recepción de datos
while(Serial2.available()>0){        //Mientras haya datos en el buffer ejecutara la funcion
  delay(5); //Retardo para recepción de datos
  
  datos[posicion]= Serial2.read();   //Leer un carácter del string
  posicion++;             //Aumentamos la variable en 1 para ir leyendo los datos de llegada uno a uno
  segmentacion = true;    //Después de la recepción de datos, aprobamos (true) para entrar a segmentación de datos
}
posicion = 0;             //Encerramos el contador de posición para empezar de nuevo en la próxima recepción de datos
//Segmentacion de datos
if (segmentacion == true){
  int index = 0;
  resultado = strtok( datos, separador );   //Separar datos  correrspondientes a C, F y K
  while ((resultado!= NULL) && (index < 3)){
    valores[index++] = atoi(resultado);      //Almacenar los datos segmentados en el array y los trasformamos de string a entero
    resultado = strtok( NULL, separador );   //Anulamos los resultados para una próxima segmentación
  }
  segmentacion = false;           //Después de la segmentación lo desaprobamos (false) hasta nuevos datos de recepción
}
Grados_Cent = valores[0];     //Leer los datos correspondientes a grados Centigrados en la posición 0 del array
Grados_Fahr = valores[1];     //Leer los datos correspondientes a grados Fahrenheit en la posición 0 del array
Grados_Kelv = valores[2];     //Leer los datos correspondientes a grados Kelvin en la posición 0 del array

//impresion en la pantalla LCD 
if((millis() - Tiempo_LCD) > 500){
  
  lcd.clear();            //limpiar pantalla
  lcd.setCursor(0,1);     //fijar el cursor de la pantalla en 0,1
  lcd.print(Grados_Cent); //imprimimos temperatura en grados centigrados
  lcd.print("C");         // Imprimir unidad
  
  lcd.setCursor(6,1);     //fijar el cursor de la pantalla en 6,1
  lcd.print(Grados_Fahr); //imprimimos temperatura en grados Fahrenheit
  lcd.print("F");         // Imprimir unidad

    lcd.setCursor(11,1);  //fijar el cursor de la pantalla en 11,1
  lcd.print(Grados_Kelv); //imprimimos temperatura en grados Kelvin
  lcd.print("K");         // Imprimir unidad
  Tiempo_LCD = millis();  //Tiempo de actualización
}
//Transmision de datos
if ((millis() - Tiempo_Tx)> 500){
  if((Grados_Cent >=20)&&(Grados_Cent <= 25)){
    lcd.setCursor(0,0);                //fijar el cursor de la pantalla en 0,0
    lcd.print("TEMPERATURA NORMAL");   //imprimimos comentario
    Serial2.print("n");                  //Enviar el carácter n
  }
  else if (Grados_Cent < 20){
    lcd.setCursor(0,0);                 //fijar el cursor de la pantalla en 0,0
    lcd.print("TEMPERATURA BAJA");      //imprimimos comentario
    Serial2.print("b");                  //Enviar el carácter b
  }
  else if (Grados_Cent > 25){
    lcd.setCursor(0,0);                 //fijar el cursor de la pantalla en 0,0
    lcd.print("TEMPERATURA ALTA");      //imprimimos comentario
    Serial2.print("a");                  //Enviar el carácter a 
  }
  Tiempo_Tx = millis();
}

}
